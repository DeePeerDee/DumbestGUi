#include <windows.h>
#include "resource.h"

HWND hToolbar = NULL;

LRESULT CALLBACK ToolDlgProc(
    _In_ HWND hwnd,
    _In_ UINT Message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{
  switch (Message)
  {
  case WM_COMMAND:
    switch (LOWORD(wParam))
    {
    case IDC_PRESS:
      MessageBox(
          hwnd,
          "Hi!",
          "Message Window 1",
          MB_OK | MB_ICONEXCLAMATION);
      break;
    case IDC_OTHER:
      MessageBox(
          hwnd,
          "Bye!",
          "Message Window 2",
          MB_OK | MB_ICONEXCLAMATION);
      break;
    }
    break;
  default:
    return FALSE;
  }

  return TRUE;
}

/**
 * Define a callback function:
 * - Most likely a Window Event Listener
 */

LRESULT CALLBACK WndProc(
    _In_ HWND hwnd,
    _In_ UINT msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{

  switch (msg)
  {
  case WM_CREATE:
  {
    HICON hIcon, hIconSm;
    HMENU hMenu, hSubMenu;

    hToolbar = CreateDialog(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDD_TOOLBAR),
        hwnd,
        ToolDlgProc);

    hMenu = CreateMenu();

    hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&File");

    hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, ID_STUFF_GO, "&Go");
    AppendMenu(hSubMenu, MF_STRING | MF_DISABLED | MF_GRAYED, ID_STUFF_GO_SOMEWHERE_ELSE, "G&o somewhere else");
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&Stuff");

    hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, ID_DIALOG_SHOW, "&Show");
    AppendMenu(hSubMenu, MF_STRING, ID_DIALOG_HIDE, "&Hide");
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "&Dialog");

    SetMenu(hwnd, hMenu);
  }
  break;
  case WM_CLOSE:
    DestroyWindow(hwnd);
    break;
  case WM_DESTROY:
    DestroyWindow(hToolbar);
    PostQuitMessage(0);
    break;
  case WM_COMMAND:
    switch (LOWORD(wParam))
    {
    case ID_DIALOG_SHOW:
      ShowWindow(hToolbar, SW_SHOW);
      break;
    case ID_DIALOG_HIDE:
      ShowWindow(hToolbar, SW_HIDE);
      break;
    }
    break;
  default:
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  return 0;
}

/**
 * Define main entry point init:
 * - Define window class
 * - Window Handling event
 * - Message Modal for Catching
 */
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR pCmdLine,
    _In_ int nCmdShow)
{
  WNDCLASSEX wc;
  HWND hwnd;
  MSG Msg;

  /**
   * Define Window Class Model
   */
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = 0;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
  wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
  wc.lpszClassName = "MyWindowClass";
  wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);

  /**
   * Register defined model into the OS: Dispatch error message if failed to register to the OS
   */
  if (!RegisterClassEx(&wc))
  {
    MessageBox(
        NULL,
        "Windows Registration Failed!",
        "Error",
        MB_ICONEXCLAMATION | MB_OK);
  }

  /**
   * Define a Window handle to prepare for model rendering
   */
  hwnd = CreateWindowEx(
      WS_EX_WINDOWEDGE,
      "MyWindowClass",
      "Test GUI",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      NULL,
      NULL,
      hInstance,
      NULL);

  /**
   * If unable to allocate memory dispatch error message
   */
  if (hwnd == NULL)
  {
    MessageBox(
        NULL,
        "Window Creation Failed",
        "Error",
        MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  /**
   * Display Window and update
   */
  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  /**
   * Retrieve a message while not quit, translate and dispatch messages into the window
   */
  while (GetMessage(&Msg, NULL, 0, 0) > 0)
  {
    if (!IsDialogMessage(hToolbar, &Msg))
    {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
    }
  }

  /**
   * Return Word Parameter
   */
  return Msg.wParam;
}