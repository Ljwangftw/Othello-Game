#ifndef POSITION_H
#define POSITION_H



class Position {
protected:
    char piece; //b,w,-,or *

public:
    explicit Position(char piece);
    virtual ~Position();
    //Accessor for piece char
    virtual char getPiece() const;

    //Setter for piece char
    void setPiece(char piece);

    virtual bool canPlay() const = 0;
};

#endif //POSITION_H
