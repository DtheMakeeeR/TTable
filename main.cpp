#include "TScanTable.h"
#include "TSortTable.h"
void main() {
	TScanTable<int, int> st;
	TSortTable<int, int> sortT;
	for (int i = 4; i >= 0; i--) {
		st.Insert(i, i * i);
	}
	st.Insert(8, 94);
	st.Insert(89, 73);
	st.Insert(11, 4);
	st.Insert(-637, 238219);
	st.Insert(-1000, -90);
	for (int i = 4; i >= 0; i--) {
		sortT.Insert(i, i * i);
	}
	TSortTable<int, int> qsort = st;
	/*for (st.Reset(); !st.IsEnd(); st.GoNext()) {
		cout << st.GetCurrKey() << " - " << st.GetCurrVal() << endl;
	}*/
	cout << st;
	cout << endl << sortT;
	cout << endl << qsort;
}