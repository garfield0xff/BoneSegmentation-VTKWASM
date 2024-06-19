#pragma once
class StatusMessage
{
public:
	static std::string Format(int slice, int maxSlice, int axis)
	{
		std::stringstream tmp;
		std::string s_axis[3] = { "Coronal", "Sagittal", "Axial" };

		tmp << s_axis[axis] << slice + 1 << " / " << maxSlice + 1;
		return tmp.str();
	}

};
