//
// Created by mustang on 18-6-10.
//


/*FOLDER'S_FUNCTION_IMPLEMENTATION_BEGIN*/
#include "Folder.h"

Message::~Message()
{
    rem_from_Folder();
}

void Folder::addMsg(Message *m)
{
    message.insert(m);
}

void Folder::reMeg(Message *m)
{
    message.erase(m);
}

std::ostream &Folder::print(std::ostream &os)
{
    for (const auto &it:message)
    {
        os << it->contents << " ";
    }
    return os;
}

// 把本Folder添加至与ori关联的message
void Folder::add_to_Message( const  Folder &ori)
{
    if (this == &ori)
    {
        std::cout<< "fuckSelf" <<std::endl;
        return;
    }

    for ( const auto &msg:ori.message)
    {
        msg->addFolder(this);
    }
}

Folder::Folder(const Folder&ori):message(ori.message)
{
    add_to_Message(ori);
}


// 把本Folder从所有与自己关联的Message中的folders删除
void Folder::remove_from_Messages()
{
    while(!message.empty())
    {
        // 这句代码是真的精巧
        (*message.begin())->remove(this);

    }
}

Folder& Folder::operator=(const Folder&ori)
{
    if(this==&ori)
    {
        std::cout<< "fuckself" <<std::endl;
        return *this;
    }
    remove_from_Messages();
    message = ori.message;
    add_to_Message(ori);
    return *this;
}

Folder::~Folder()
{
    remove_from_Messages();
}
/*FOLDER'S_FUNCTION_IMPLEMENTATION_BEGIN*/



/*MESSAGE'S_FUNCTION_IMPLEMENTATION_BEGIN*/

std::ostream& Message::print(std::ostream&os)
{
    std::cout << folders.size() << " ";
    return os;
}


void Message::save(Folder &target)
{
    folders.insert(&target);
    target.addMsg(this);
}

void Message::remove(Folder &target)
{
    folders.erase(&target);
    target.reMeg(this);
}

void Message::addFolder(Folder *f)
{
    folders.insert(f);
}

void Message::remove(Folder* f)
{
    folders.erase(f);
    f->reMeg(this);
}

/*MESSAGE'S_FUNCTION_IMPLEMENTATION_BEGIN*/


void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    if (lhs == rhs)
    {
        std::cout << "SwapfuckSelf" << std::endl;
        return;
    }


    for (auto f:lhs.folders)
    {
        f->reMeg(&lhs);
    }

    for (auto f:rhs.folders)
    {
        f->reMeg(&rhs);
    }
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    for (auto f:lhs.folders)
    {
        f->addMsg(&lhs);
    }
    for (auto f:rhs.folders)
    {
        f->addMsg(&rhs);
    }
}
