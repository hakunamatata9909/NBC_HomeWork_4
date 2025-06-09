#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    static const int totalStock = 3;  // ��� å ��� 3������ ����
    int currentRent;                  // ���� �뿩 ���� �Ǽ�

    Book(const string& t, const string& a)
        : title(t), author(a), currentRent(0) {
    }

    int available() const {
        return totalStock - currentRent;
    }
};

class BookManager {
private:
    vector<Book> books;

public:
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author));
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << "\n";
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�.\n";
            return;
        }
        cout << "=== ���� ��� (����/��) ===\n";
        for (const auto& b : books) {
            cout << "- \"" << b.title << "\" by " << b.author
                << "  [ " << b.available() << " / " << Book::totalStock << " ]\n";
        }
    }

    // �������� �뿩
    void rentByTitle(const string& title) {
        for (auto& b : books) {
            if (b.title == title) {
                if (b.available() > 0) {
                    b.currentRent++;
                    cout << "\"" << title << "\" �뿩 �Ϸ�! ���� �Ǽ�: "
                        << b.available() << "\n";
                }
                else {
                    cout << "\"" << title << "\" �� ���� �Ǽ��� �����ϴ�.\n";
                }
                return;
            }
        }
        cout << "�ش� ������ å�� ã�� �� �����ϴ�: " << title << "\n";
    }

    // �۰��� �뿩 (ù ��° ��Ī ����)
    void rentByAuthor(const string& author) {
        for (auto& b : books) {
            if (b.author == author) {
                if (b.available() > 0) {
                    b.currentRent++;
                    cout << "\"" << b.title << "\" (by " << author << ") �뿩 �Ϸ�! ���� �Ǽ�: "
                        << b.available() << "\n";
                }
                else {
                    cout << "by " << author << " �� ��� å�� �뿩 ���Դϴ�.\n";
                }
                return;
            }
        }
        cout << "�ش� �۰��� å�� ã�� �� �����ϴ�: " << author << "\n";
    }

    // �������� �ݳ�
    void returnByTitle(const string& title) {
        for (auto& b : books) {
            if (b.title == title) {
                if (b.currentRent > 0) {
                    b.currentRent--;
                    cout << "\"" << title << "\" �ݳ� �Ϸ�! ���� �Ǽ�: "
                        << b.available() << "\n";
                }
                else {
                    cout << "\"" << title << "\" ��(��) ���� �뿩 ���� �ƴմϴ�.\n";
                }
                return;
            }
        }
        cout << "�ش� ������ å�� ã�� �� �����ϴ�: " << title << "\n";
    }

    // �۰��� �ݳ� (ù ��° ��Ī ����)
    void returnByAuthor(const string& author) {
        for (auto& b : books) {
            if (b.author == author) {
                if (b.currentRent > 0) {
                    b.currentRent--;
                    cout << "\"" << b.title << "\" (by " << author << ") �ݳ� �Ϸ�! ���� �Ǽ�: "
                        << b.available() << "\n";
                }
                else {
                    cout << "by " << author << " �� å�� ���� �뿩 ���� �ƴմϴ�.\n";
                }
                return;
            }
        }
        cout << "�ش� �۰��� å�� ã�� �� �����ϴ�: " << author << "\n";
    }
};

int main() {
    BookManager manager;
    while (true) {
        cout << "\n=== ������ ���� ���α׷� ===\n"
            << "1. å �߰�\n"
            << "2. ��� å ���\n"
            << "3. å �뿩\n"
            << "4. å �ݳ�\n"
            << "5. ����\n"
            << "����: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, author;
            cout << "å ����: ";     getline(cin, title);
            cout << "å ����: ";     getline(cin, author);
            manager.addBook(title, author);
        }
        else if (choice == 2) {
            manager.displayAllBooks();
        }
        else if (choice == 3 || choice == 4) {
            cout << (choice == 3 ? "�뿩" : "�ݳ�") << " ����� �����ϼ���:\n"
                << "1. ��������\n"
                << "2. �۰���\n"
                << "����: ";
            int sub;
            cin >> sub;
            cin.ignore();
            if (sub == 1) {
                string title;
                cout << "å ����: "; getline(cin, title);
                if (choice == 3) manager.rentByTitle(title);
                else          manager.returnByTitle(title);
            }
            else if (sub == 2) {
                string author;
                cout << "å ����: "; getline(cin, author);
                if (choice == 3) manager.rentByAuthor(author);
                else          manager.returnByAuthor(author);
            }
            else {
                cout << "�߸��� �Է��Դϴ�.\n";
            }
        }
        else if (choice == 5) {
            cout << "���α׷��� �����մϴ�.\n";
            break;
        }
        else {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n";
        }
    }
    return 0;
}
