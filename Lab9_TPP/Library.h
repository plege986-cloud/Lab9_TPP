#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
namespace before
{
struct Book
{
    std::string title, author;
    void display() const
    {
        std::cout << "Title: " << title << ", Author: " << author << '\n';
    }
    void saveToDatabase() const
    {
        std::cout << "Saving book to database...\n";
    }
    void sendEmailNotification() const
    {
        std::cout << "Sending email notification about the new book...\n";
    }
};
class Library
{
    std::vector<Book> books;

  public:
    void addBook(const Book &b)
    {
        books.push_back(b);
        b.saveToDatabase();
        b.sendEmailNotification();
    }
    void displayBooks() const
    {
        for (const auto &b : books)
            b.display();
    }
};
}
namespace after
{
class Book
{
    std::string title_, author_;

  public:
    Book(std::string t, std::string a) : title_(std::move(t)), author_(std::move(a))
    {
    }
    const std::string &title() const
    {
        return title_;
    }
    const std::string &author() const
    {
        return author_;
    }
};
struct IBookStorage
{
    virtual void save(const Book &) = 0;
    virtual const std::vector<Book> &all() const = 0;
    virtual ~IBookStorage() = default;
};
struct INotifier
{
    virtual void notify(const Book &) = 0;
    virtual ~INotifier() = default;
};
class MemoryStorage : public IBookStorage
{
    std::vector<Book> books;

  public:
    void save(const Book &b) override
    {
        books.push_back(b);
        std::cout << "Saving book to database...\n";
    }
    const std::vector<Book> &all() const override
    {
        return books;
    }
};
class EmailNotifier : public INotifier
{
  public:
    void notify(const Book &) override
    {
        std::cout << "Sending email notification about the new book...\n";
    }
};
class BookDisplay
{
  public:
    static void display(const Book &b)
    {
        std::cout << "Title: " << b.title() << ", Author: " << b.author() << '\n';
    }
};
class Library
{
    IBookStorage &storage;
    INotifier &notifier;

  public:
    Library(IBookStorage &s, INotifier &n) : storage(s), notifier(n)
    {
    }
    void addBook(const Book &b)
    {
        storage.save(b);
        notifier.notify(b);
    }
    void displayBooks() const
    {
        for (const auto &b : storage.all())
            BookDisplay::display(b);
    }
};
}
