#ifndef H_EVENTHANDLER
#define H_EVENTHANDLER

class cEventHandler
{
public:
    /// Destructor, sets instanceFlag to false so getInstance creates new on request
    ~cEventHandler() { instanceFlag_ = false; }

    /// Returns singleton pointer
    static cEventHandler* getInstance();

    /// Update method to parse events
    void update();

private:
    /// private constructor because singleton. Instance is gotten from getInstance
    cEventHandler() {}

    /// Flag to tell if instance made or not
    static bool instanceFlag_;

    /// Pointer to this class if instance made.
    static cEventHandler* thisPointer_;


};
#endif
