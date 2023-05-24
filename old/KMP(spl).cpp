#include <bits/stdc++.h>
using namespace std;
void computeLPSArray(string pattern, int M, int lps[]);


void KMPSearch(string pattern, string text)
{
	int M = pattern.size();
	int N = text.size();


	int lps[M];


	computeLPSArray(pattern, M, lps);
	cout<<"lps is->";
	for(int i=0;i<M;i++)
        cout<<" "<<lps[i]<<" ";
    cout<<endl;

	int i = 0;
	int j = 0;
	while ((N - i) >= (M - j)) {
		if (pattern[j] == text[i]) {
			j++;
			i++;
		}

		if (j == M) {
			printf("Found pattern at index %d\n", i - j);
			j = lps[j - 1];
		}


		else if (i < N && pattern[j] != text[i]) {

			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
}


void computeLPSArray(string pattern, int M, int lps[])
{

	int len = 0;

	lps[0] = 0;
	int i = 1;
	while (i < M) {
		if (pattern[i] == pattern[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else {
			if (len != 0) {
				len = lps[len - 1];


			}
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}


int main()
{
	string text ;
	//= "ABABDABACDABABCABAB";
	cin>>text;
	string pattern;
	//= "ABABCABAB";
	cin>>pattern;
	KMPSearch(pattern, text);
	return 0;
}

