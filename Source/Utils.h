#pragma once

/// Clamp a value between two values
inline int Clamp(int inValue, int inMin, int inMax)
{
	return inValue < inMin ? inMin : inValue > inMax ? inMax : inValue;
}