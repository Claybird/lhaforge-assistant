#pragma once

std::vector<std::wstring> UtilGetCommandLineArgs();

std::wstring UtilRegQueryString(HKEY hKey, const std::wstring& path);
LSTATUS UtilRegSetKeyAndValue(HKEY root, const std::wstring& keyPath, const std::wstring& name, const std::wstring& value);

template <typename mapclass,typename keyclass>
bool has_key(const mapclass &theMap,keyclass theKey){
	return theMap.find(theKey)!=theMap.end();
}

std::filesystem::path UtilGetModulePath();
std::filesystem::path UtilGetModuleDirectoryPath();

inline std::wstring toUpper(const std::wstring& input) {
	std::wstring output;
	std::transform(input.begin(), input.end(), std::back_inserter(output),
		[](wchar_t c) {
		return towupper(c);
	});
	return output;
}
template <typename T>
T Argument(T value) noexcept
{
	return value;
}
template <typename T>
T const* Argument(std::basic_string<T> const& value) noexcept
{
	return value.c_str();
}
template <typename ...Args>
std::wstring Format(const std::wstring& fmt, Args && ...args)
{
	//snprintf_s will not return the required buffer size
	std::wstring work;
#pragma warning(push)
#pragma warning(disable:4996)
	auto size = _snwprintf(nullptr, 0, fmt.c_str(), Argument(args)...);
	work.resize(size + 1);
	_snwprintf(&work[0], work.size(), fmt.c_str(), Argument(args)...);
#pragma warning(pop)
	return work.c_str();
}

//loads string from resource
std::wstring UtilLoadString(UINT uID);
