#include <iostream>
#include <unordered_map>
#include <stdexcept>

class AssociatedEntities {
private:
    std::unordered_map<int, std::string> entityMap;

public:
    // Функція для додавання асоціативної пари
    void add_association(int entity1, const std::string& entity2) {
        entityMap[entity1] = entity2;
    }

    // Перевантаження оператора [] для доступу до асоціативних сутностей
    std::string& operator[](int entity1) {
        if (entityMap.find(entity1) == entityMap.end()) {
            throw std::invalid_argument("Entity not found.");
        }
        return entityMap[entity1];
    }
};

int main() {
    AssociatedEntities entities;

    // Додавання асоціативних сутностей
    entities.add_association(1, "one");
    entities.add_association(10, "ten");

    try {
        std::cout << entities[1] << std::endl;
        std::cout << entities[10] << std::endl;
        std::cout << entities[5] << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    system("pause");
    return 0;
}
