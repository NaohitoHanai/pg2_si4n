#pragma once

/// <summary>
/// Window‚Ì’è‹`‚ð‚µ‚Ü‚·
/// </summary>
namespace Screen
{
	static const int WIDTH = 1280;
	static const int HEIGHT = 720;
#ifdef _DEBUG
	static const BOOL WINDOW_MODE = TRUE;
#else
	static const BOOL WINDOW_MODE = FALSE;
#endif
	static const char* WINDOW_NAME = "project";
	static const float WINDOW_EXTEND = 1.0f;
};
