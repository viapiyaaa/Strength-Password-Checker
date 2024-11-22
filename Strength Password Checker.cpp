#include <iostream>
#include <fstream>
using namespace std;

#define ef else if
#define el else

struct User {
  string username;
  string password;
  int strength;
  int possBase;
  int possExpo;
};

void welcome() {
    cout << "===============================================================" << endl;
    cout << "        SELAMAT DATANG DI PROGRAM STRENGTH PASSWORD CHECKER    " << endl;
    cout << "===============================================================" << endl;
}

int checkVary (int& active, int check) {
  if (active != check) { active = check; return 3; }
  ef (active == check) { return 1; }

  return 0;
}

int checkStrength(string& password, int& possBase, int& possExpo) {


  int redos = 0; // Re-do (Spam)
  int upper = 0; // Kapital
  int lower = 0; // Normal
  int digit = 0; // Angka
  int punct = 0; // Simbol
  int active = 0;

  for (int i = 0; i < password.length(); i++) {
    char c = password[i];
    if (c == ' ') return false;

    if (isupper(c)) upper += checkVary(active,1);
    ef (islower(c)) lower += checkVary(active,2);
    ef (isdigit(c)) digit += checkVary(active,3);
    ef (ispunct(c)) punct += checkVary(active,4);

    if (isupper(c) || islower(c)) {
      char c2 = password[i+1];
      if (tolower(c) == tolower(c2)) redos++;
    }
  }

  int pBase = 0;
  if (upper != 0) pBase += 26;
  if (lower != 0) pBase += 26;
  if (digit != 0) pBase += 10;
  if (punct != 0) pBase += 30;

  possBase = pBase;
  possExpo = password.length();

  int varys = upper + lower + digit + punct;
  int pLast = varys*100 + pBase*password.length() - redos*100;

  pLast /= 40;
  if (pLast > 100) pLast = 100;

  return pLast;
}

bool registerUser(User& user) {
  string pilihan;

  while (true) {
    cout << "Registrasi (Ya/Tidak): ";
    cin >> pilihan;
    cout << endl;

    if (pilihan == "Ya" || pilihan == "ya") {
      cout << "Masukkan username: ";
      cin >> user.username;

      cout << "Masukkan password: ";
      cin >> user.password;

      user.strength = checkStrength(user.password,user.possBase,user.possExpo);
      if (user.strength < 50) {
        cout << endl << "Kekuatan password hanya " << user.strength << "%";
        cout << endl << "Silahkan registrasi ulang!\n\n";
        continue;
      }

      cout << endl << "Selamat anda telah terdaftar!" << endl;
      cout << "Username: " << user.username << endl;
      cout << "Password: " << user.password << endl;
      cout << "Strength: " << user.strength << "%" << endl;
      cout << "Pass Try: " << user.possBase << "^" << user.possExpo << " x tries" << endl;

      return true;
    }
    else if (pilihan == "Tidak" || pilihan == "tidak") {
      cout << "Registrasi dibatalkan" << endl;
      return false;
    }
    else {
      cout << "Input tidak valid. Silakan masukkan 'Ya' atau 'Tidak'." << endl;
    }
  }
}

void print(User& user) {
  ofstream file;
  file.open("user.txt", ios::app);
  file << "Username: " << user.username << endl;
  file << "Password: " << user.password << endl;
  file << "Strength: " << user.strength << "%" << endl;
  file << "Pass Try: " << user.possBase << "^" << user.possExpo << " x tries" << endl;
  file << endl;
  file .close();
}

int main() {
  welcome();
  User user;
  double isRegistered = registerUser(user);

  if (isRegistered) {
    print(user);
  }
  system ("pause");

  return 0;
}
