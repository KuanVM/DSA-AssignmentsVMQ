#include<iostream>

using namespace std;

struct Node
{
    int He_so;
    int Luy_thua;
    Node* Ke_tiep;
};


Node* TaoNode(int He_so, int Luy_thua)
{
    Node* q = new Node();
    q->He_so = He_so;
    q->Luy_thua = Luy_thua;
    q->Ke_tiep = NULL;
    return q;
}


void ThemNode(Node*& Dau, int He_so, int Luy_thua)
{
    Node* newNode = TaoNode(He_so, Luy_thua);
    if (Dau == NULL || Luy_thua > Dau->Luy_thua)
    {
        newNode->Ke_tiep = Dau;
        Dau = newNode;
    }
    else
    {
        Node* q = Dau;
        while (q->Ke_tiep != NULL && q->Ke_tiep->Luy_thua > Luy_thua)
        {
            q = q->Ke_tiep;
        }
        newNode->Ke_tiep = q->Ke_tiep;
        q->Ke_tiep = newNode;
    }
}


Node* Tong2ham(Node* ham1, Node* ham2) {
    Node* kq = NULL;
    Node* a = ham1;
    Node* b = ham2;
    while (a != NULL && b != NULL) {
        if (a->Luy_thua > b->Luy_thua) {
            ThemNode(kq, a->He_so, a->Luy_thua);
            a = a->Ke_tiep;
        }
        else if (a->Luy_thua < b->Luy_thua) {
            ThemNode(kq, b->He_so, b->Luy_thua);
            b = b->Ke_tiep;
        }
        else {
            int TongHe_so = a->He_so + b->He_so;
            if (TongHe_so != 0) {
                ThemNode(kq, TongHe_so, a->Luy_thua);
            }
            a = a->Ke_tiep;
            b = b->Ke_tiep;
        }
    }
    while (a != NULL) {
        ThemNode(kq, a->He_so, a->Luy_thua);
        a = a->Ke_tiep;
    }
    while (b != NULL) {
        ThemNode(kq, b->He_so, b->Luy_thua);
        b = b->Ke_tiep;
    }
    return kq;
}


void aoaNode(Node*& Dau) {
    while (Dau != NULL && Dau->He_so == 0) {
        Node* q = Dau;
        Dau = Dau->Ke_tiep;
        delete q;
    }
    Node* t = Dau;
    while (t != NULL && t->Ke_tiep != NULL) {
        if (t->Ke_tiep->He_so == 0) {
            Node* q = t->Ke_tiep;
            t->Ke_tiep = q->Ke_tiep->Ke_tiep;
            delete q;
        }
        else {
            t = t->Ke_tiep;
        }
    }
}


void NhapHam(Node*& Dau)
{
    int n;
    cout << "Nhap so phan tu: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int He_so, Luy_thua;
        cout << "Nhap he so & so mu: ";
        cin >> He_so >> Luy_thua;
        ThemNode(Dau, He_so, Luy_thua);
        if (Dau->He_so == 0) {
            aoaNode(Dau);
        }
    }
}

void Inham(Node* Dau)
{
    Node* q = Dau;
    while (q != NULL)
    {
        if (q->He_so > 0 && q != Dau) {
            cout << "+";
        }
        if (q->Luy_thua == 0) {
            cout << q->He_so;
        }
        else if (q->He_so == 1 && q->Luy_thua != 0) {
            cout << "x^" << q->Luy_thua;
        }
        else if (q->Luy_thua == 1) {
            cout << q->He_so << "x";
        }
        else {
            cout << q->He_so << "x^" << q->Luy_thua;
        }
        q = q->Ke_tiep;
    }
}


int main() {
    Node* dt1 = NULL;
    Node* dt2 = NULL;

    NhapHam(dt1);
    NhapHam(dt2);
    Inham(dt1);
    cout << endl;
    Inham(dt2);
    cout << endl;
    Node* kq = Tong2ham(dt1, dt2);
    Inham(kq);
    cout << endl;
}




