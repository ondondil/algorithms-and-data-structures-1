#include <iostream>

class Tree
{
private:
    struct Node
    {
        Node *parent;
        Node *children;
        int value;
        int c_size;
    };
    Node *root;
    void add_child(Node &n, int *branch, int bs, int bp);
    void traverse_preorder(const Node &n) const;
    void destructor_helper(Node &n);
public:
    Tree();
    ~Tree();
    void push_branch(int *branch, int size);
    void print_tree() const;
};

Tree::Tree()
{
    root = new Node;
    root->parent = nullptr;
    root->children = nullptr;
    root->c_size = 0;
    root->value = 0;
}

Tree::~Tree()
{
    destructor_helper(*root);
}

void Tree::add_child(Node &n, int *branch, int bs, int bp)
{
    if (bp == bs)
    {
        return;
    }
    // Przeszukiwanie dzieci w poszukiwaniu pasującego
    bool match = false;
    int matching_child_index = -1;
    for (int i = 0; i < n.c_size && !match; ++i)
    {
        if (n.children[i].value == branch[bp])
        {
            matching_child_index = i;
            match = true;
        }
    }

    if (!match)
    {
        // Dodaj nowe dziecko z wartością branch[bp] po czym wywołaj add_child z bp+1
        if (n.c_size == 0)
        {
            n.c_size = 1;   // Jak najmniejsze tablice
            n.children = new Node [n.c_size];
            n.children[0].value = branch[bp];
            n.children[0].c_size = 0;
            n.children[0].parent = &n;
            n.children[0].children = nullptr;
            add_child(n.children[0], branch, bs, bp + 1);
        }
        else
        {
            Node *tmp = new Node [n.c_size + 1];
            for (int j = 0; j < n.c_size; ++j)
            {
                tmp[j] = n.children[j];
                /*
                 * Przepisanie tablicy zmienia adresy rodziców dla dzieci
                 * poszczególnych elementów tablicy, przez co potrzebne jest
                 * nadanie tym dzieciom nowych adresów rodziców będących
                 * elementami nowej tablicy.
                 */
                if (tmp[j].children != nullptr)
                {
                    for (int k = 0; k < tmp[j].c_size; ++k)
                    {
                        tmp[j].children[k].parent = &(tmp[j]);
                    }
                }
            }
            delete [] n.children;
            n.children = tmp;
            n.children[n.c_size].value = branch[bp];
            n.children[n.c_size].c_size = 0;
            n.children[n.c_size].parent = &n;
            n.children[n.c_size].children = nullptr;
            ++(n.c_size);
            add_child(n.children[n.c_size - 1], branch, bs, bp + 1);
        }
    }
    else
    {
        add_child(n.children[matching_child_index], branch, bs, bp + 1);
    }
}

void Tree::traverse_preorder(const Node &n) const
{
    std::cout << n.value << " ";
    if (n.c_size != 0)
    {
        for (int i = 0; i < n.c_size; ++i)
        {
            traverse_preorder(n.children[i]);
        }
    }
}

void Tree::destructor_helper(Tree::Node &n)
{
    if (n.children != nullptr)
    {
        for (int i = 0; i < n.c_size; ++i)
        {
            destructor_helper(n.children[i]);
        }
        delete [] n.children;
    }
}

void Tree::push_branch(int *branch, int size)
{
    add_child(*root, branch, size, 0);
}

void Tree::print_tree() const
{
    if (root->c_size != 0)
    {
        for (int i = 0; i < root->c_size; ++i)
        {
            traverse_preorder(root->children[i]);
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    // Liczba wpisów
    int entries_no;
    std::cin >> entries_no;

    Tree t;

    // Wczytywanie wpisów
    int numbers_no;
    int *branch = new int[10000];
    for (int i = 0; i < entries_no; ++i)
    {
        std::cin >> numbers_no;
        for (int j = 0; j < numbers_no; ++j)
        {
            std::cin >> branch[j];
        }
        t.push_branch(branch, numbers_no);
    }

    t.print_tree();

    return 0;
}
