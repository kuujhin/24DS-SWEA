#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{

	FILE *sfp;
	sfp = freopen("1240_in.txt", "r", stdin);

	int num;
	cin >> num;

	for (int i = 0; i < num; i++)
	{
		int n, m;
		cin >> n >> m;

		string temp;
		vector<string> code;
		for (int j = 0; j < n; j++)
		{
			cin >> temp;
			if (temp.find('1') != string::npos)
			{
				code.push_back(temp.substr(temp.rfind('1') - 55, 56));
			}
		}

		string num[10] = {"0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011"};
		int result[10];

		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				if (code[0].substr(j * 7, 7) == num[k])
				{
					result[j] = k;
				}
			}
		}

		int checkcode = (result[0] + result[2] + result[4] + result[6]) * 3 + result[1] + result[3] + result[5] + result[7];

		if (checkcode % 10 == 0)
		{
			int answer = result[1] + result[3] + result[5] + result[7] + result[2] + result[4] + result[6] + result[0];
			cout << "#" << i + 1 << " " << answer << "\n";
		}
		else
		{
			cout << "#" << i + 1 << " " << 0 << "\n";
		}
	}

	fclose(sfp);
	return 0;
}