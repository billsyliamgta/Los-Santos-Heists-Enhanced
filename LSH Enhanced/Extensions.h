#pragma once
/// <summary>
/// A class implementing custom structs similar to the ones in System.Drawing in C#.
/// </summary>
class Extensions
{
public:
	struct Vector3
	{
	public:
		float x;
		float y;
		float z;
	};

	struct Point
	{
	public:
		int x;
		int y;

		Point(int _x, int _y) : x(_x), y(_y) {}
	};

	struct PointF
	{
	public:
		float x;
		float y;

		PointF(float _x, float _y) : x(_x), y(_y) {}

		PointF() {}
	};

	struct Size
	{
	public:
		int Width;
		int Height;
	};

	struct SizeF
	{
	public:
		float Width;
		float Height;

		SizeF(float w, float h) : Width(w), Height(h) {}

		SizeF() {}
	};

	struct Color
	{
	public:
		int R; // Red
		int G; // Green
		int B; // Blue
		int A; // Alpha

		Color(int _r, int _g, int _b, int _a) : R(_r), G(_g), B(_b), A(_a) {}
	};
};