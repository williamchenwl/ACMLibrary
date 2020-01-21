/*
    REPLACE 
*/
template<class Data>
class KMP_Pattern{

private:
    vector<Data> patString;
    vector<int> pat;
public:
    KMP_Pattern(const string& s) {
        for (auto ch : s) patString.push_back(ch);
        pat.resize(patString.length(), 0);
        int pre = -1, pat[0] = -1;
        for (int i = 1; i < patString.length(); i++) { 
            while(patString[i] != patString[pre+1] && pre != -1) {
                pre = pat[pre];
            } 
            if (patString[i] == patString[pre+1]) {
                pre++;
            }
            pat[i] = pre;

        }
    }

    int kmp(const string& mainString) {
        int pre = -1, count = 0;
        for (int i = 0;i < mainString.length();i++) {
            while (mainString[i] != patString[pre + 1] && pre != -1) {
                pre = pat[pre];
            }
            if (mainString[i] == patString[pre + 1]) {
                pre++;
            }
            if (pre == patString.length()) {
                count++;
                pre = pat[pre];
            }
        }
        return count;
    }
}