#include "global.hpp"
//各种类与json类的互相转换函数
void to_json(json &j, const Food &p)
{
    j = {{"type", food}, {"title", p.title}, {"detail", p.detail}, {"price", p.price}, {"discount", p.discount}, {"stock", p.stock}};
}

void from_json(const json &j, Food &p)
{
    j.at("title").get_to(p.title);
    j.at("detail").get_to(p.detail);
    j.at("price").get_to(p.price);
    j.at("discount").get_to(p.discount);
    j.at("stock").get_to(p.stock);
}

void to_json(json &j, const Clothing &p)
{
    j = {{"type", food}, {"title", p.title}, {"detail", p.detail}, {"price", p.price}, {"discount", p.discount}, {"stock", p.stock}};
}

void from_json(const json &j, Clothing &p)
{
    j.at("title").get_to(p.title);
    j.at("detail").get_to(p.detail);
    j.at("price").get_to(p.price);
    j.at("discount").get_to(p.discount);
    j.at("stock").get_to(p.stock);
}

void to_json(json &j, const Book &p)
{
    j = {{"type", food}, {"title", p.title}, {"detail", p.detail}, {"price", p.price}, {"discount", p.discount}, {"stock", p.stock}};
}

void from_json(const json &j, Book &p)
{
    j.at("title").get_to(p.title);
    j.at("detail").get_to(p.detail);
    j.at("price").get_to(p.price);
    j.at("discount").get_to(p.discount);
    j.at("stock").get_to(p.stock);
}

void to_json(json &j, const Client &p)
{
    j = {{"type", client}, {"name", p.name}, {"passwd", p.passwd}, {"balance", p.balance}};
}

void from_json(const json &j, Client &p)
{
    j.at("name").get_to(p.name);
    j.at("passwd").get_to(p.passwd);
    j.at("balance").get_to(p.balance);
}

void to_json(json &j, const Business &p)
{
    j = {{"type", business}, {"name", p.name}, {"passwd", p.passwd}, {"balance", p.balance}, {"myShelves", p.myShelves}};
}

void from_json(const json &j, Business &p)
{
    j.at("name").get_to(p.name);
    j.at("passwd").get_to(p.passwd);
    j.at("balance").get_to(p.balance);
    j.at("myShelves").get_to(p.myShelves);
}

