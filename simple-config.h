#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <unordered_map>
#include <list>
#include <regex>


class config
{
private:
	void parse(std::istream& in) {
		static const std::regex comment_regex{ R"x(\s*[;#])x" };
		static const std::regex section_regex{ R"x(\s*\[([^\]]+)\])x" };
		static const std::regex value_regex{ R"x(\s*(\S[^ \t=:]*)\s*[=:]\s*((\s?\S+)+)\s*$)x" };
		std::string current_section = "";
		std::smatch pieces;
		for (std::string line; std::getline(in, line);)
		{
			if (line.empty() || std::regex_match(line, pieces, comment_regex)) {
				// skip comment lines and blank lines                    
			}
			else if (std::regex_match(line, pieces, section_regex)) {
				if (pieces.size() == 2) { // exactly one match
					current_section = pieces[1].str();
				}
			}
			else if (std::regex_match(line, pieces, value_regex)) {
				if (pieces.size() == 4) { // exactly enough matches
					inimap[current_section][pieces[1].str()] = pieces[2].str();
				}
			}
		}
	}

	void serialize(std::ostream& out) const {
		try
		{
			for (const auto &kvs : GetSection())
				out << kvs.first << '=' << kvs.second << std::endl;

			out << std::endl;
		}
		catch (std::out_of_range)
		{
		}

		for (const auto &heading : inimap)
			if (!heading.first.empty()) {
				out << "[" << heading.first << "]" << std::endl;
				for (const auto &kvs : heading.second)
					out << kvs.first << '=' << kvs.second << std::endl;

				out << std::endl;
			}
	}

	using SectionMap = std::unordered_map<std::string, std::string>;
	using IniMap = std::unordered_map<std::string, SectionMap>;

	IniMap inimap;

public:
	config(std::istream& in) { parse(in); }
	std::ostream& operator << (std::ostream &out) { serialize(out); return out; }
	
	// No copycats allowed! Only real cats need apply.
	config(const config&) = delete;
	config& operator = (const config&) = delete;

	// Standard iterators be iterated here.
	typedef IniMap::iterator iterator;
	iterator begin() { return inimap.begin(); }
	iterator end() { return inimap.end(); }
	IniMap const GetIniMap() const { return inimap; }

	SectionMap const GetSection() const { return GetSection(""); }
	SectionMap const GetSection(const std::string& section) const { return inimap.at(section); }

	std::string const GetValue(const std::string& key) const { return GetValue("", key); }
	std::string const GetValue(const std::string& section, const std::string& key) const
	{
		try
		{
			const auto sectionMap = GetSection(section);
			try
			{
				return sectionMap.at(key);
			}
			catch (std::out_of_range)
			{
				return "";
			}
		}
		catch (std::out_of_range)
		{
			return "";
		}
	}

	bool const SetValue(const std::string& key, const std::string& value) { return SetValue("", key, value); }
	bool const SetValue(const std::string& section, const std::string& key, const std::string& value)
	{
		try
		{
			inimap[section][key] = value;
		}
		catch (std::out_of_range)
		{
			return false;
		}

		return true;
	}
};

#endif // CONFIG_H_