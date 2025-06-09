#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    static const int totalStock = 3;  // 모든 책 재고 3권으로 통일
    int currentRent;                  // 현재 대여 중인 권수

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
        cout << "책이 추가되었습니다: " << title << " by " << author << "\n";
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다.\n";
            return;
        }
        cout << "=== 도서 목록 (가용/총) ===\n";
        for (const auto& b : books) {
            cout << "- \"" << b.title << "\" by " << b.author
                << "  [ " << b.available() << " / " << Book::totalStock << " ]\n";
        }
    }

    // 제목으로 대여
    void rentByTitle(const string& title) {
        for (auto& b : books) {
            if (b.title == title) {
                if (b.available() > 0) {
                    b.currentRent++;
                    cout << "\"" << title << "\" 대여 완료! 남은 권수: "
                        << b.available() << "\n";
                }
                else {
                    cout << "\"" << title << "\" 의 가용 권수가 없습니다.\n";
                }
                return;
            }
        }
        cout << "해당 제목의 책을 찾을 수 없습니다: " << title << "\n";
    }

    // 작가로 대여 (첫 번째 매칭 도서)
    void rentByAuthor(const string& author) {
        for (auto& b : books) {
            if (b.author == author) {
                if (b.available() > 0) {
                    b.currentRent++;
                    cout << "\"" << b.title << "\" (by " << author << ") 대여 완료! 남은 권수: "
                        << b.available() << "\n";
                }
                else {
                    cout << "by " << author << " 의 모든 책이 대여 중입니다.\n";
                }
                return;
            }
        }
        cout << "해당 작가의 책을 찾을 수 없습니다: " << author << "\n";
    }

    // 제목으로 반납
    void returnByTitle(const string& title) {
        for (auto& b : books) {
            if (b.title == title) {
                if (b.currentRent > 0) {
                    b.currentRent--;
                    cout << "\"" << title << "\" 반납 완료! 남은 권수: "
                        << b.available() << "\n";
                }
                else {
                    cout << "\"" << title << "\" 은(는) 현재 대여 중이 아닙니다.\n";
                }
                return;
            }
        }
        cout << "해당 제목의 책을 찾을 수 없습니다: " << title << "\n";
    }

    // 작가로 반납 (첫 번째 매칭 도서)
    void returnByAuthor(const string& author) {
        for (auto& b : books) {
            if (b.author == author) {
                if (b.currentRent > 0) {
                    b.currentRent--;
                    cout << "\"" << b.title << "\" (by " << author << ") 반납 완료! 남은 권수: "
                        << b.available() << "\n";
                }
                else {
                    cout << "by " << author << " 의 책은 현재 대여 중이 아닙니다.\n";
                }
                return;
            }
        }
        cout << "해당 작가의 책을 찾을 수 없습니다: " << author << "\n";
    }
};

int main() {
    BookManager manager;
    while (true) {
        cout << "\n=== 도서관 관리 프로그램 ===\n"
            << "1. 책 추가\n"
            << "2. 모든 책 출력\n"
            << "3. 책 대여\n"
            << "4. 책 반납\n"
            << "5. 종료\n"
            << "선택: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, author;
            cout << "책 제목: ";     getline(cin, title);
            cout << "책 저자: ";     getline(cin, author);
            manager.addBook(title, author);
        }
        else if (choice == 2) {
            manager.displayAllBooks();
        }
        else if (choice == 3 || choice == 4) {
            cout << (choice == 3 ? "대여" : "반납") << " 방식을 선택하세요:\n"
                << "1. 제목으로\n"
                << "2. 작가로\n"
                << "선택: ";
            int sub;
            cin >> sub;
            cin.ignore();
            if (sub == 1) {
                string title;
                cout << "책 제목: "; getline(cin, title);
                if (choice == 3) manager.rentByTitle(title);
                else          manager.returnByTitle(title);
            }
            else if (sub == 2) {
                string author;
                cout << "책 저자: "; getline(cin, author);
                if (choice == 3) manager.rentByAuthor(author);
                else          manager.returnByAuthor(author);
            }
            else {
                cout << "잘못된 입력입니다.\n";
            }
        }
        else if (choice == 5) {
            cout << "프로그램을 종료합니다.\n";
            break;
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도하세요.\n";
        }
    }
    return 0;
}
