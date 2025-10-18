#include <windows.h>

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
  case WM_LBUTTONDOWN:
  {
    char fileName[MAX_PATH];
    HINSTANCE hInstance = GetModuleHandle(NULL);

    GetModuleFileName(hInstance, fileName, MAX_PATH);
    MessageBox(hwnd, fileName, "Custom Message", MB_OK | MB_ICONINFORMATION);
  }
  case WM_CLOSE:
    DestroyWindow(hwnd);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_PAINT:
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    EndPaint(hwnd, &ps);
    return 0;
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
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
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "MyWindowClass";
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

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
      WS_EX_CLIENTEDGE,
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
    TranslateMessage(&Msg);
    DispatchMessage(&Msg);
  }

  /**
   * Return Word Parameter
   */
  return Msg.wParam;
}