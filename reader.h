#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
const int bitness = 8;
namespace vb
{

	//class vaibin
	//{
	//public:

	class NUMBER_SYSTEM
	{
	public:

		string chars = "0123456789ABCD;=";
		string closecharbin = "1110";
		int len = 16;
		int bitness = 4;

	};

	NUMBER_SYSTEM main_ns;

	int BinToDec(string bin)
	{
		int binlen = bin.length() - 1;
		int num = 0;
		for (size_t i = 0; i < bin.length(); i++)
		{
			if (bin[i] == '0')
			{
				num += 0;
			}
			else if (bin[i] == '1')
			{
				num += int(bin[i] - '0') * pow(2, binlen - i);
			}
		}
		return num;
	}

	string DecToBin(int dec)
	{
		string output = "";
		int len = 0;
		while (dec >> len > 0)
		{
			output += to_string((dec >> len) % 2);
			len++;
		}
		reverse(output.begin(), output.end());
		return output;
	}

	string ReadFile(string path)
	{
		fstream file;
		file.open(path);
		string time_t;
		string filetxt = "";
		while (getline(file, time_t)) {
			filetxt += time_t;
		}
		file.close();
		return filetxt;
	}

	void WriteFile(string input, string path)
	{
		fstream file;
		file.open(path);
		file << input;
		file.close();
	}

	string GetBinChar(char c)
	{
		int k = 128;
		string bin = "";
		while (k > 0) {
			bin += to_string(bool(c & k));
			k = k >> 1;
		};
		return bin;
	}

	string GetBinText(string inputtxt)
	{
		string bin_chars = "";
		string timermaptrext;
		for (size_t i = 0; i < inputtxt.length(); i++)
		{
			bin_chars += GetBinChar(inputtxt[i]);
		}
		return bin_chars;
	}

	string GetBinFile(string path)
	{
		string bin_chars = "";
		fstream file;
		file.open(path);
		string timermaptrext;
		string txt = "";
		while (getline(file, timermaptrext)) {
			txt += timermaptrext;
		}
		for (size_t i = 0; i < txt.length(); i++)
		{
			bin_chars += GetBinChar(txt[i]);
		}
		return bin_chars;
		file.close();
	}

	void SetBinFile(string bin, string path)
	{
		string output;
		fstream file;
		file.open(path);
		if (bin.length() % bitness == 0)
		{
			for (size_t i = 0; i < bin.length() / bitness; i++)
			{
				string tt = "";
				for (size_t l = 0; l < bitness; l++)
				{
					tt += bin[i * bitness + l];
				}
				char charset(BinToDec(tt));
				output += charset;
			}
		}
		else
		{
			cout << endl << "ERROR: BIN % 8 != 0";
		}
		file << output;
		file.close();
	}

	string SetBinString(string bin)
	{
		string output;
		if (bin.length() % bitness == 0)
		{
			for (size_t i = 0; i < bin.length() / bitness; i++)
			{
				string tt = "";
				for (size_t l = 0; l < bitness; l++)
				{
					tt += bin[i * bitness + l];
				}
				char charset(BinToDec(tt));
				output += charset;
			}
		}
		else
		{
			cout << endl << "ERROR: BIN % 8 != 0";
		}
		return output;
	}

	string CreateNSBin(string input, NUMBER_SYSTEM ns)
	{
		string output = "";
		for (size_t i = 0; i < input.length(); i++)
		{
			string tt = "";
			tt = DecToBin(ns.chars.find_first_of(input[i]));
			while (tt.length() < 4)
			{
				tt = "0" + tt;
			}
			output += tt;
		}
		if (input.length() % (bitness / ns.bitness) != 0)
		{
			output += ns.closecharbin;
		}
		return output;
	}

	string GetNSBin(string input, NUMBER_SYSTEM ns)
	{
		string output = "";
		for (size_t i = 0; i < input.length(); i += ns.bitness)
		{
			string bin = "";
			for (size_t l = 0; l < ns.bitness; l++)
			{
				bin += input[i + l];
			}
			output += ns.chars[BinToDec(bin)];
		}
		return output;
	}

	map<string, string> ReadConf(string input)
	{
		map <string, string> output;
		string t = "";
		string tt = "";
		for (size_t i = 0; i < input.length(); i++)
		{
			if (input[i] != ' ')
			{
				while (input[i] != '=')
				{
					if (input[i] != ' ')
					{
						t += input[i];
					}
					i++;
				}
				i++;
				while (input[i] != ';')
				{
					if (input[i] != ' ')
					{
						tt += input[i];
					}
					i++;
				}
				output[t] = tt;
				t = "";
				tt = "";
			}
		}
		return output;
	}

	map<string, string> ReadConfFile(string path)
	{
		fstream file;
		file.open(path);
		string time_t;
		string filetxt = "";
		while (getline(file, time_t)) {
			filetxt += time_t;
		}
		map <string, string> output;
		string t = "";
		string tt = "";
		for (size_t i = 0; i < filetxt.length(); i++)
		{
			if (filetxt[i] != ' ')
			{
				while (filetxt[i] != '=')
				{
					if (filetxt[i] != ' ')
					{
						t += filetxt[i];
					}
					i++;
				}
				i++;
				while (filetxt[i] != ';')
				{
					if (filetxt[i] != ' ')
					{
						tt += filetxt[i];
					}
					i++;
				}
				output[t] = tt;
				t = "";
				tt = "";
			}
		}
		file.close();
		return output;
	}

	string WriteConf(map<string, string> input)
	{
		string output = "";
		for (auto& item : input)
		{
			output += item.first + "=" + item.second + ";";
		}
		return output;
	}

	void WriteConfFile(map<string, string> input, string path)
	{
		fstream file;
		file.open(path);
		string output = "";
		for (auto& item : input)
		{
			output += item.first + "=" + item.second + ";";
		}
		file << output;
		file.close();
	}

	string BeautiferConf(string input)
	{
		string t = "";
		string tt = "";
		string output = "";
		for (size_t i = 0; i < input.length(); i++)
		{
			if (input[i] != ' ')
			{
				while (input[i] != '=')
				{
					if (input[i] != ' ')
					{
						t += input[i];
					}
					i++;
				}
				output += t;
				output += " = ";
				i++;
				while (input[i] != ';')
				{
					if (input[i] != ' ')
					{
						tt += input[i];
					}
					i++;
				}
				output += tt;
				output += ";\n";
				t = "";
				tt = "";
			}
		}
		return output;
	}

	vector<string> ReadVectorConfFile(string path)
	{
		fstream file;
		file.open(path);
		string time_t;
		string filetxt = "";
		while (getline(file, time_t)) {
			filetxt += time_t;
		}
		vector<string> output;
		string t = "";
		string tt = "";
		for (size_t i = 0; i < filetxt.length(); i++)
		{
			if (filetxt[i] != ' ')
			{
				while (filetxt[i] != ';')
				{
					if (filetxt[i] != ' ')
					{
						tt += filetxt[i];
					}
					i++;
				}
				output.push_back(tt);
				t = "";
				tt = "";
			}
		}
		file.close();
		return output;
	}

	/*inline map<string, string> parse_XML(string input, unsigned int begin_input, unsigned int end_input)
	{
		map<string, string> xml;
		unsigned in_len = end_input - begin_input;
		for  (unsigned int i = 0; i < in_len; i++)
		{

		}
		return xml;
	}

	map<string, string> VAI_XML_READ(string input)
	{
		unsigned int in_len = input.length();
		string pre_str = "";
		string ps = "";
		for (unsigned int i = 0; i < in_len; i++)
		{
			if (input[i] == '<')
			{
				i++;
				while (input[i] != '>')
				{
					pre_str += input[i];
				}
				i++;
				while (input[i] != '<')
				{

				}

			}
		}
	}*/
}
