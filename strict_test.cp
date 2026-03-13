// C+ Strict Semicolon Test
def greet(name) {
    if (name == None) {
        print("Hello, Stranger!");
    } elif (name == "Admin") {
        print("Welcome, System Administrator.");
    } else {
        print("Hello, " + name + "!");
    };
};

greet("Admin");
greet(None);
greet("User");

let i = 0;
while (i < 5) {
    i = i + 1;
    print(i);
};

if (True and not False) {
    print("Strict compliance reached!");
};
