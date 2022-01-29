#include<string>
using namespace std;
typedef string ListElemType;

class inord_list{
	public:
	inord_list();
	~inord_list();
	bool insert(const ListElemType &e, int LineNumber);
	bool first(ListElemType &e);
	bool next(ListElemType &e);
	bool getLineNumber(int &LineNumber);
	int getOcc();

	private:
	struct Node;
	struct smallNode;
	typedef Node* Link;
	typedef smallNode* smallLink;
	struct Node{
		ListElemType elem;
		int occ;
		smallLink smallHead;
		smallLink smallTail;
		smallLink smallCurrent;
		Link Next;
	};
	struct smallNode{
		int ln_num;
		smallLink smallNext;
	};
	Link Head;
	Link Tail;
	Link Current;
};
