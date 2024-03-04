#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char ** argv) {

	FILE * sfp;
	sfp = freopen("1216_in.txt", "r", stdin);
	
	for (int i = 0; i < 10; i++) {
		int num;
		cin >> num;

		vector<string> words(100);
		for (int j = 0; j < 100; j++) cin >> words[j];
		
		bool isFind = false;
		int length = 100;
		int ans = 1;
		while (!isFind && length > 1) {
			for (int j = 0; j < 100; j++) {
				for (int k = 0; k <= 100 - length; k++) {

					bool isPalin = true;
					for (int l = 0; l < length / 2; l++) {
						if (words[j][k + l] != words[j][k + length - 1 - l]) {
							isPalin = false;
							break;
						}
					}
					if (isPalin) {
						cout << "#" << num << " " << length << "\n";
						isFind = true;
						break;
					}

					isPalin = true;
					for (int l = 0; l < length / 2; l++) {
						if (words[k + l][j] != words[k + length - 1 - l][j]) {
							isPalin = false;
							break;
						}
					}
					if (isPalin) {
						cout << "#" << num << " " << length << "\n";
						isFind = true;
						break;
					}
				}
				if (isFind) break;
			}

			length--;
			
		}
	}
	fclose(sfp);
	return 0;
}