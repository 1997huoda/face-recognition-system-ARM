#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<string> name;
    string receive = "lajfl/asjdflkjdsf/ajkflsdfjs/gbhg/renming/";
    string tmp;
    for (int i = 0; i < receive.size(); i++) {
        if (receive[i] != '/') {
            tmp.push_back(receive[i]);
        } else {
            name.push_back(tmp);
            tmp.clear();
        }
    }
    for (int i = 0; i < name.size(); i++) {
        cout << name[i] << endl;
    }
    return 0;
}
