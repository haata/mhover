/*
 * Copyright (c) 2009 Jacob Alexander <haata at users.sf.net>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name(s) of the above
 * copyright holders shall not be used in advertising or otherwise
 * to promote the sale, use or other dealings in this Software
 * without prior written authorization.
 */

// Local Includes
#include "MHover.h"


// Hook Callback **********************************************************************************

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam )
{
	// Find Mouse Wheel Message
	switch ( nCode )
	{
	case HC_ACTION:
		switch ( wParam )
		{
		case WM_MOUSEWHEEL:
			return curMHoverInst->verticalWheelScroll( wParam, lParam );
		}
		break;
	}

	return CallNextHookEx( 0, nCode, wParam, lParam);
}


// Constructor/Destructor *************************************************************************

MHover::MHover( HINSTANCE hInstance )
{
	// Event Loop Object
	m_LoopEvent = CreateEvent( NULL, 1, 0, NULL );

	// Mousewheel hook
	m_hook = SetWindowsHookEx( WH_MOUSE_LL, HookProc, hInstance, 0 );
}

MHover::~MHover()
{
	// Cleanup
	curMHoverInst = NULL;
	UnhookWindowsHookEx( m_hook );
}


// Utility Functions ******************************************************************************

HWND MHover::findHoveredWindow( int nSleep )
{
	// Mouse Position
	POINT curPos;

	// Couldn't get cursor position for some reason
	if ( ::GetCursorPos( &curPos ) )
		return ::WindowFromPoint( curPos );

	return NULL;
}

LRESULT MHover::verticalWheelScroll( WPARAM wParam, LPARAM lParam )
{
	// Send the scroll Message to the Window under the cursor
	::SendMessage( findHoveredWindow( 10 ), WM_MOUSEWHEEL, ( (MSLLHOOKSTRUCT*)lParam )->mouseData, 0 );

	// Important to send 1 (not 0) or the scroll event will progagate to some applications (e.g. Explorer)
	return 1;
}

