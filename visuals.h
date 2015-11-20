#define FONT_HEIGHT 16
class CVisuals
{
public:
	unsigned long font;
	unsigned long MenuFont;
	unsigned long MediumMenuFont;
	unsigned long SmallMenuFont;

	/*TODO: Remove this function*/
	void DrawWatermark()
	{

		this->DrawStringA(5, 5, 255, 255, 255, 255, "Weeabot V1.0");

	}

	void Draw3DBox(const Vector &mins, const Vector &maxs, Color c)
	{
		Vector diff = maxs - mins;
		Vector pointsToDraw[24] = {
			// Bottom Horizontal lines
			mins, mins + Vector(diff.x, 0, 0), // 1 - 2
			mins + Vector(diff.x, 0, 0), mins + Vector(diff.x, diff.y, 0), // 2 - 3
			mins + Vector(diff.x, diff.y, 0), mins + Vector(0, diff.y, 0), // 3 - 4
			mins + Vector(0, diff.y, 0), mins, // 4 - 1

			// Vertical Lines

			mins, mins + Vector(0, 0, diff.z), // 1 - 6
			mins + Vector(diff.x, 0, 0), mins + Vector(diff.x, 0, diff.z), // 2 - 7
			mins + Vector(diff.x, diff.y, 0), mins + Vector(diff.x, diff.y, diff.z), // 3 - 8
			mins + Vector(0, diff.y, 0), mins + Vector(0, diff.y, diff.z), // 4 - 5

			// Top Horizontal lines.
			maxs, maxs - Vector(diff.x, 0, 0), // 8 - 5
			maxs - Vector(diff.x, 0, 0), maxs - Vector(diff.x, diff.y, 0), // 5 - 6
			maxs - Vector(diff.x, diff.y, 0), maxs - Vector(0, diff.y, 0), // 6 - 7
			maxs - Vector(0, diff.y, 0), maxs // 7 - 8
		};
		Vector startPos, endPos;
		for (int i = 0; i < 24; i += 2)
		{
			if (WorldToScreen(pointsToDraw[i], startPos))
			{
				if (WorldToScreen(pointsToDraw[i + 1], endPos))
					DrawLine(startPos.x, startPos.y, endPos.x, endPos.y, c);
			}
		}


	}

	class screensize
	{
	public:
		int iScreenWidth;
		int iScreenHeight;
	};

	bool WorldToScreen(Vector &origin, Vector &screen)
	{
		const VMatrix worldToScreen = Interfaces.Engine->WorldToScreenMatrix();
		float w = worldToScreen[3][0] * origin[0] + worldToScreen[3][1] * origin[1] + worldToScreen[3][2] * origin[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
		screen.z = 0; //Screen doesn't have a 3rd dimension.
		static screensize gScreenSize;
		Interfaces.Engine->GetScreenSize(gScreenSize.iScreenWidth, gScreenSize.iScreenHeight);

		if (w > 0.001) //If the object is within view.
		{
			float fl1DBw = 1 / w; //Divide 1 by the angle.
			screen.x = (gScreenSize.iScreenWidth / 2) + (0.5 * ((worldToScreen[0][0] * origin[0] + worldToScreen[0][1] * origin[1] + worldToScreen[0][2] * origin[2] + worldToScreen[0][3]) * fl1DBw) * gScreenSize.iScreenWidth + 0.5); //Get the X dimension and push it in to the Vector.
			screen.y = (gScreenSize.iScreenHeight / 2) - (0.5 * ((worldToScreen[1][0] * origin[0] + worldToScreen[1][1] * origin[1] + worldToScreen[1][2] * origin[2] + worldToScreen[1][3]) * fl1DBw) * gScreenSize.iScreenHeight + 0.5); //Get the Y dimension and push it in to the Vector.
			return true;
		}

		return false;
	}

	void DrawLine(int x, int y, int w, int h, Color c)
	{
		Interfaces.Surface->DrawSetColor(c);
		Interfaces.Surface->DrawLine(x, y, w, h);
	}

	void GetTextSize(int font, const char* text, int& W, int& H)
	{
		va_list list;
		char buffer[1024];
		va_start(list, text);
		vsprintf(buffer, text, list);
		va_end(list);
		wchar_t sstring[1024];
		const size_t size = strlen(buffer) + 1;
		mbstowcs(sstring, buffer, size);

		//Interfaces.Surface->GetTextSize(font, sstring, *W, *H);
		typedef void(__thiscall* Fn)(void*, unsigned long, const wchar_t*, int&, int&);
		((Fn)VMT.GetFunction( Interfaces.Surface, 75 ))( Interfaces.Surface, font, sstring, W, H );
	}

	/*Draws string with custom font*/
	void DrawStringA(int x, int y, int r, int g, int b, int a, const char* text, ...)
	{
		Interfaces.Surface->DrawSetTextPos(x, y);
		Interfaces.Surface->DrawSetTextColor(r, g, b, a);
		Interfaces.Surface->DrawSetTextFont(font);
		va_list list;
		char buffer[1024];
		va_start(list, text);
		vsprintf(buffer, text, list);
		va_end(list);
		wchar_t sstring[1024];
		const size_t size = strlen(buffer) + 1;
		mbstowcs(sstring, buffer, size);
		Interfaces.Surface->DrawPrintText(sstring, wcslen(sstring));
	}

	/*Draws string with ingame font*/
	void DrawStringB(int x, int y, int r, int g, int b, int a, const char* text, ...)
	{
		Interfaces.Surface->DrawSetTextPos(x, y);
		Interfaces.Surface->DrawSetTextColor(r, g, b, a);
		Interfaces.Surface->DrawSetTextFont(5);
		va_list list;
		char buffer[1024];
		va_start(list, text);
		vsprintf(buffer, text, list);
		va_end(list);
		wchar_t sstring[1024];
		const size_t size = strlen(buffer) + 1;
		mbstowcs(sstring, buffer, size);
		Interfaces.Surface->DrawPrintText(sstring, wcslen(sstring));
	}

	/*Draw string with custom font*/
	void DrawStringC(int font, int x, int y, int r, int g, int b, int a, const char* text, ...)
	{
		Interfaces.Surface->DrawSetTextPos(x, y);
		Interfaces.Surface->DrawSetTextColor(r, g, b, a);
		Interfaces.Surface->DrawSetTextFont(font);
		va_list list;
		char buffer[1024];
		va_start(list, text);
		vsprintf(buffer, text, list);
		va_end(list);
		wchar_t sstring[1024];
		const size_t size = strlen(buffer) + 1;
		mbstowcs(sstring, buffer, size);
		Interfaces.Surface->DrawPrintText(sstring, wcslen(sstring));
	}

	void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a)
	{
		Interfaces.Surface->DrawSetColor(r, g, b, a);
		Interfaces.Surface->DrawFilledRect(x, y, x + w, y + h);
	}

	void DrawRect(int x, int y, int w, int h, Color Col)
	{
		int r, g, b, a;
		Col.GetColor(r, g, b, a);

		Interfaces.Surface->DrawSetColor(r, g, b, a);
		Interfaces.Surface->DrawFilledRect(x, y, x + w, y + h);
	}

	void DrawOutlinedRect(int x, int y, int w, int h, int r, int g, int b, int a)
	{
		Interfaces.Surface->DrawSetColor(r, g, b, a);
		Interfaces.Surface->DrawOutlinedRect(x, y, x + w, y + h);
	}

	void DrawOutlinedRect(int x, int y, int w, int h, Color Col)
	{
		int r, g, b, a;
		Col.GetColor(r, g, b, a);

		Interfaces.Surface->DrawSetColor(r, g, b, a);
		Interfaces.Surface->DrawOutlinedRect(x, y, x + w, y + h);
	}

	void DrawCircle(int x, int y, int diameter, Color Col)
	{

		int r, g, b, a;
		Col.GetColor(r, g, b, a);

		Interfaces.Surface->DrawSetColor(r, g, b, a);

		int quality = 50;
		diameter = diameter * 0.5;

		Interfaces.Surface->DrawSetTexture(0);

		Vertex_t  * vert;
		vert = new Vertex_t[quality];

		for (int i = 1; i <= quality; i++)
		{
			float ang = ((i * 360) * M_PI / 180.0) / quality;

			vec_t lx = x + diameter * cos(ang);
			vec_t ly = y + diameter * sin(ang);

			vert[i - 1].Init(Vector2D(lx, ly), Vector2D(lx, ly));
		}

		Interfaces.Surface->DrawTexturedPolygon(quality, vert);

		delete[] vert;

	}

	float GetDistance(Vector x, Vector y)
	{
		Vector delta;
		delta = y - x;
		return sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
	}

}; CVisuals Visuals;