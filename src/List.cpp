#include "List.h"

class CList::CImplementation{
public:
    class node{
    public:
        int value;
        std::shared_ptr<node> next;
        node(int value, std::shared_ptr<node> next = nullptr) : value(value), next(next){
        }
        ~node(){
            next.reset();
        }
    };
    std::shared_ptr<node> new_node(int value, std::shared_ptr<node> next = nullptr){
        std::shared_ptr<node> temp = std::make_shared<node>(value, next);
        return temp;
    }
    std::shared_ptr<node> head;
    std::shared_ptr<node> tail;
    int size;
};

//-----------------------------------------------------------------------------------------------
//----------------------------------------iterator-----------------------------------------------
class CList::iterator::CImplementation{
    friend class CList;
public:
    int index;
    std::shared_ptr<CList::CImplementation::node> head;
    std::shared_ptr<CList::CImplementation::node> curNode;
};

CList::iterator::iterator() : DData(std::make_unique<CImplementation>()){
    DData->head = nullptr;
    DData->curNode = nullptr;
    DData->index = 0;
}

CList::iterator::iterator(const iterator &iter) : DData(std::make_unique<CImplementation>()){
    *this = iter;
}

CList::iterator::~iterator() = default;

CList::iterator& CList::iterator::operator=(const iterator &iter){
    DData->head = iter.DData->head;
    DData->index = iter.DData->index;
    DData->curNode = iter.DData->curNode;
    return *this;
}

bool CList::iterator::operator==(const iterator &iter) const{
    if (iter.DData->curNode == nullptr && DData->curNode == nullptr) {
        return true;
    } else if (DData->head->next != iter.DData->head->next) {
        return false;
    } else {
        return DData->index == iter.DData->index;
    }
    
}

bool CList::iterator::operator!=(const iterator &iter) const{
    return !(*this==iter);
}

CList::iterator& CList::iterator::operator++(){
    DData->index++;
    DData->curNode = DData->curNode->next;
    return *this;
}

CList::iterator CList::iterator::operator++(int){
    return ++(*this);
}

CList::iterator& CList::iterator::operator--(){
    DData->index--;
    auto temp = DData->head;
    while (temp != DData->curNode) {
        if (temp != nullptr) {
            temp = temp->next;
        } else{
            break;
        }
    }
    temp.swap(DData->curNode);
    temp.reset();
    return *this;
}

CList::iterator CList::iterator::operator--(int){
    return --(*this);
}

CList::iterator& CList::iterator::operator+=(size_type inc){
    DData->index += inc;
    for(unsigned int i = 0; i < inc; i++){
        DData->curNode = DData->curNode->next;
    }
    return *this;
}

CList::iterator CList::iterator::operator+(size_type inc) const{
    CList::iterator copy(*this);
    return copy += inc;
}

CList::iterator operator+(CList::size_type inc, const CList::iterator &iter){
    return iter + inc;
}

CList::iterator& CList::iterator::operator-=(size_type inc){
    DData->index -= inc;
    auto temp = DData->head;
    for (int i = 0; i < DData->index; i++) {
        temp = temp->next;
    }
    temp.swap(DData->curNode);
    temp.reset();
    return *this;
}

CList::iterator CList::iterator::operator-(size_type inc) const{
    CList::iterator copy(*this);
    return copy -= inc;
}

CList::iterator::reference CList::iterator::operator*() const{
    return DData->curNode->value;
}

CList::iterator::pointer CList::iterator::operator->() const{
    return &(*(*this));
}

//-----------------------------------------------------------------------------------------------
//-------------------------------------const_iterator--------------------------------------------
class CList::const_iterator::CImplementation{
    friend class CList;
public:
    int index;
    std::shared_ptr<CList::CImplementation::node> head;
};

CList::const_iterator::const_iterator() : DData(std::make_unique<CImplementation>()){
    DData->index = 0;
    DData->head = nullptr;
}

CList::const_iterator::const_iterator(const const_iterator &iter) : DData(std::make_unique<CImplementation>()){
    *this = iter;
}

//convert iter to const_iter
CList::const_iterator::const_iterator(const iterator &iter) : DData(std::make_unique<CImplementation>()){
    DData->head = std::make_shared<CList::CImplementation::node>(*(iter.DData->head));
    DData->index = iter.DData->index;
}

CList::const_iterator::~const_iterator(){
    DData->head.reset();
    DData.release();
}


CList::const_iterator& CList::const_iterator::operator=(const const_iterator &iter){
    
    DData->head = std::make_shared<CList::CImplementation::node>(*(iter.DData->head));
    DData->index = iter.DData->index;
    return *this;
}

bool CList::const_iterator::operator==(const const_iterator &iter) const{
    if (DData->head->next != iter.DData->head->next) {
        return false;
    } else{
        return DData->index == iter.DData->index;
    }
}


bool CList::const_iterator::operator!=(const const_iterator &iter) const{
    return !(*this==iter);
}

CList::const_iterator& CList::const_iterator::operator++(){
    DData->index++;
    return *this;
}

CList::const_iterator CList::const_iterator::operator++(int){
    return ++(*this);
}

CList::const_iterator& CList::const_iterator::operator--(){
    DData->index--;
    return *this;
}

CList::const_iterator CList::const_iterator::operator--(int){
    return --(*this);
}

CList::const_iterator& CList::const_iterator::operator+=(size_type inc){
    DData->index += inc;
    return *this;
}

CList::const_iterator CList::const_iterator::operator+(size_type inc) const{
    CList::const_iterator copy(*this);
    return copy += inc;
}

CList::const_iterator operator+(CList::size_type inc, const CList::const_iterator &iter){
    return iter + inc;
}

CList::const_iterator& CList::const_iterator::operator-=(size_type inc){
    DData->index -= inc;
    return *this;
}

CList::const_iterator CList::const_iterator::operator-(size_type inc) const{
    CList::const_iterator copy(*this);
    return copy -= inc;
}

CList::const_iterator::reference CList::const_iterator::operator*() const{
    auto temp = DData->head;
    for (int i = 0; i < DData->index; i++) {
        temp = temp->next;
    }
    return temp->value;
}

CList::const_iterator::pointer CList::const_iterator::operator->() const{
    return &(*(*this));
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------CList-------------------------------------------------
CList::CList() : DData(std::make_unique< CImplementation >()){
    DData->size = 0;
    DData->tail = nullptr;
    DData->head = nullptr;
}

CList::~CList() = default;

bool CList::IsEmpty() const noexcept{
    return DData->size == 0;
}

int CList::Count() const noexcept{
    return DData->size;
}

CList::reference CList::Front(){
    return DData->head->value;
}

CList::const_reference CList::Front() const{
    return DData->head->value;
}

CList::reference CList::Back(){
    return DData->tail->value;
}

CList::const_reference CList::Back() const{
    return DData->tail->value;
}

void CList::PushFront(int val){
    DData->size ++;
    DData->head = DData->new_node(val, DData->head);
    if (DData->tail == nullptr) {
        DData->tail = DData->head;//must be new if tail ==null
    }
}

void CList::PushBack(int val){
    DData->size ++;
    if (DData->tail == nullptr) {
        DData->tail = DData->new_node(val);
        DData->head = DData->tail;//must be new if tail ==null
    } else{
        DData->tail->next = DData->new_node(val);
        DData->tail = DData->tail->next;
    }
}

void CList::PopFront(){
    DData->size--;
    if (DData->size == 0) {
        DData->tail = nullptr;
        DData->head = nullptr;
    } else{
        
        auto temp = DData->head->next;
        DData->head->~node();
        DData->head = temp;
        temp.reset();
    }
}

void CList::PopBack(){
    DData->size--;
    if (DData->size == 0) {
        DData->tail = nullptr;
        DData->head = nullptr;
    } else{
        auto temp = DData->head;
        for (int i = 1; i < DData->size; i++) {
            temp = temp->next;
        }
        DData->tail.reset();
        DData->tail = temp;
        temp.reset();
        DData->tail->next.reset();
    }
}

CList::iterator CList::begin(){
    iterator temp;
    temp.DData->head = DData->head;
    temp.DData->curNode = DData->head;
    temp.DData->index = 0;
    return temp;
}

CList::const_iterator CList::begin() const{
    const_iterator temp;
    temp.DData->head = DData->head;
    temp.DData->index = 0;
    return temp;
}

CList::const_iterator CList::cbegin() const{
    return this->begin();
}

CList::iterator CList::end(){
    iterator temp;
    temp.DData->index = DData->size;
    temp.DData->head = DData->head;
    temp.DData->curNode = nullptr;
    return temp;
}

CList::const_iterator CList::end() const{
    const_iterator temp;
    temp.DData->head = DData->head;
    temp.DData->index = DData->size;
    return temp;
}

CList::const_iterator CList::cend() const{
    return this->end();
}

