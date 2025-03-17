#include "TScanTable.h"
void main() {
	TScanTable<int, int> st;
	for (int i = 0; i < 5; i++) {
		st.Insert(i, i * i);
	}
	/*for (st.Reset(); !st.IsEnd(); st.GoNext()) {
		cout << st.GetCurrKey() << " - " << st.GetCurrVal() << endl;
	}*/
	cout << st;
}