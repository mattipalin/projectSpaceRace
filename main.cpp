#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <iostream>
#include "coordinates.h"
#include <fstream>

#define BUTTON 39	
#define ANSWER_BUTTON 42

float wWidth =  800;
float wHeight = 400;

HWND TextBox;		// For creating a text field and storing its content

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance, 
					LPSTR lpCmdLine, 
					int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";

	WNDCLASSEX wc;
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//wc.lpfnWndProc = DefWindowProc;           // Commented out, Matti Palin
    wc.lpfnWndProc   = WindowProc;      // ~forward declaration of a function
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"MyWindow";
	wc.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	MSG msg;
	
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
    // Create the window.
	HWND hwnd = CreateWindowEx(
			WS_EX_OVERLAPPEDWINDOW, 
			L"MyWindow", 
			L"myTitle", 
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 
			CW_USEDEFAULT, 
			wWidth, 
			wHeight,
			NULL, 
			NULL, 
			hInstance, 
			NULL);
	
	if (!hwnd)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(		// Message handler function
                HWND hwnd,          // Handle to the windos
                UINT uMsg,          // Message code
                WPARAM wParam, LPARAM lParam        // Additional message data
                ) 
            // Defines the behaviour of the window: appearance, how it interacts with the user, etc.			
{



    switch (uMsg)
    {
    case WM_DESTROY:
	{
        PostQuitMessage(0);
        return 0;
	}
    case WM_PAINT:
        {	// WM_PAINT is run 3rd
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));      //  fills the update region with a single color

	        // Then we can insert some text
			TCHAR verbIntroductionText[ ] = L"Verb:";
			TCHAR moodIntroductionText[ ] = L"Mood:";
			TCHAR tenseIntroductionText[] = L"Tense:";
			TCHAR personIntroductionText[]= L"Person:";
			TCHAR answerIntroductionText[]= L"Answer:";
			TCHAR timeIntroductionText[]  = L"Time:";
			TextOut(hdc, 2.0/10.0*wWidth, 2.3/10.0*wHeight, verbIntroductionText, ARRAYSIZE(verbIntroductionText));
			TextOut(hdc, 2.0/10.0*wWidth, 3.3/10.0*wHeight, moodIntroductionText, ARRAYSIZE(moodIntroductionText));
			TextOut(hdc, 2.0/10.0*wWidth, 4.3/10.0*wHeight, tenseIntroductionText, ARRAYSIZE(tenseIntroductionText));
			TextOut(hdc, 2.0/10.0*wWidth, 5.3/10.0*wHeight, personIntroductionText, ARRAYSIZE(personIntroductionText));
			TextOut(hdc, 2.0/10.0*wWidth, 6.3/10.0*wHeight, answerIntroductionText, ARRAYSIZE(answerIntroductionText));
			TextOut(hdc, 2.0/10.0*wWidth, 7.3/10.0*wHeight, timeIntroductionText, ARRAYSIZE(timeIntroductionText));

            EndPaint(hwnd, &ps);
        }
	case WM_CREATE:
		{	// WM_CREATE is run first. And again 4th time


			HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			if (stdOut != NULL && stdOut != INVALID_HANDLE_VALUE)
			{
				DWORD written = 0;
				const char *message = "hello world";
				WriteConsoleA(stdOut, message, strlen(message), &written, NULL);
			}
            // Create Verb Info Box
            InfoBox VerbInfoBox(3.0/10*wWidth, 2.0/10*wHeight, 6.0/10*wWidth, 1.0/10*wHeight);      // Object: VerbInfoBox
			CreateWindowW(L"BUTTON", 								// Class name (predefined)
						L"VerbInfoBox", 								// Text in button
						WS_CHILD | WS_VISIBLE |BS_CENTER| BS_FLAT , 	// Styles
						VerbInfoBox.m_x, 
						VerbInfoBox.m_y, 
						VerbInfoBox.m_width, 
						VerbInfoBox.m_height,
						hwnd, 
						NULL, 
						NULL, 
						NULL);

            // Create Mood Info Box
            InfoBox MoodInfoBox(3.0/10*wWidth, 3.0/10*wHeight, 6.0/10*wWidth, 1.0/10*wHeight);      // Object: VerbInfoBox
			CreateWindowW(L"BUTTON", 								// Class name (predefined)
						L"MoodInfoBox", 							// Text in button
						WS_CHILD | WS_VISIBLE |BS_CENTER| BS_FLAT, 	// Styles
						MoodInfoBox.m_x, 							// Location of top-left corner, x
						MoodInfoBox.m_y, 
						MoodInfoBox.m_width, 						// Width
						MoodInfoBox.m_height, 						// Height
						hwnd, 										// Handle to a window parent
						(HMENU) BUTTON, 										// Handle to a menu / Button ID
						NULL, 
						NULL);

			// Create Tense Info Box
            InfoBox TenseInfoBox(3.0/10*wWidth, 4.0/10*wHeight, 6.0/10*wWidth, 1.0/10*wHeight);      // Object: VerbInfoBox
			CreateWindowW(L"BUTTON", 								// Class name (predefined)
						L"TenseInfoBox", 							// Text in button
						WS_CHILD | WS_VISIBLE |BS_CENTER| BS_DEFPUSHBUTTON, 	// Styles
						TenseInfoBox.m_x, 							// Location of top-left corner, x
						TenseInfoBox.m_y, 
						TenseInfoBox.m_width, 						// Width
						TenseInfoBox.m_height, 						// Height
						hwnd, 										// Handle to a window parent
						(HMENU) BUTTON, 										// Handle to a menu / Button ID
						NULL, 
						NULL);

			// Create Person Info Box
            InfoBox PersonInfoBox(3.0/10*wWidth, 5.0/10*wHeight, 6.0/10*wWidth, 1.0/10*wHeight);      // Object: VerbInfoBox
			CreateWindowW(L"BUTTON", 								// Class name (predefined)
						L"PersonInfoBox", 							// Text in button
						WS_CHILD | WS_VISIBLE |BS_CENTER| BS_DEFPUSHBUTTON, 	// Styles
						PersonInfoBox.m_x, 							// Location of top-left corner, x
						PersonInfoBox.m_y, 
						PersonInfoBox.m_width, 						// Width
						PersonInfoBox.m_height, 					// Height
						hwnd, 										// Handle to a window parent
						(HMENU) BUTTON, 							// Handle to a menu / Button ID
						NULL, 
						NULL);

			// Create AnswerPersonHintBox
			InfoBox AnswerPersonBox(3.0/10.0*wWidth, 6.0/10*wHeight, 2.0/10.0*wWidth, 1.0/10*wHeight);
						CreateWindowW(L"BUTTON", 					// Class name (predefined)
						L"AnswerPerson", 							// Text in button
						WS_CHILD | WS_VISIBLE | BS_CENTER | BS_DEFPUSHBUTTON, 	// Styles
						AnswerPersonBox.m_x, 						// Location of top-left corner, x
						AnswerPersonBox.m_y, 
						AnswerPersonBox.m_width, 					// Width
						AnswerPersonBox.m_height, 					// Height
						hwnd, 										// Handle to a window parent
						(HMENU) BUTTON, 							// Handle to a menu / Button ID
						NULL, 
						NULL);

			// Create Answer Box
            InfoBox AnswerBox(5.0/10*wWidth, 6.0/10*wHeight, 4.0/10*wWidth, 1.0/10*wHeight);      // Object: VerbInfoBox
			TextBox = CreateWindow(L"EDIT", 
						0, 
						WS_BORDER|WS_CHILD|WS_VISIBLE| ES_WANTRETURN | ES_MULTILINE, 
						AnswerBox.m_x, 
						AnswerBox.m_y, 
						AnswerBox.m_width, 
						AnswerBox.m_height, 
						hwnd, 
						(HMENU) ANSWER_BUTTON, 	
						NULL, 
						NULL);


		}
	case WM_COMMAND:		// When you click a button, the window will get this
		{	// WM_COMMAND is run second
			// WPARAM will tell which button you pressed
			if (LOWORD(wParam) == BUTTON)
			{
				MessageBox(hwnd, L"I was clicked!", L"Yay!", MB_OK | MB_ICONERROR);
			}

			if (LOWORD(wParam) == ANSWER_BUTTON)
			{
				MessageBox(hwnd, L"You pressed enter ??", L"Yay!", MB_OK | MB_ICONERROR);
			}
			
		}

	case WM_KEYDOWN:
	{
		
	    switch (wParam)
         {
          case VK_RETURN:
          MessageBox(hwnd, L"You pressed something.", L"Yay!", MB_OK | MB_ICONERROR);
              break;  //or return 0; if you don't want to pass it further to def proc
          //If not your key, skip to default:
         }
    //default:
    //     return CallWindowProc(oldEditProc, wnd, msg, wParam, lParam);
	}

        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}