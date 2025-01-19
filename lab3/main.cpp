#include "Subject.hpp"
#include "ConsoleObserver.hpp"
#include "LoggingObserver.hpp"
#include "CustomEvent.hpp"

int main() {
    Subject<int> intSubject;
    auto intConsoleObserver = std::make_shared<ConsoleObserver<int>>();
    auto intLoggingObserver = std::make_shared<LoggingObserver<int>>("int.txt");

    intSubject.attach(intConsoleObserver);
    intSubject.attach(intLoggingObserver);

    intSubject.notify(7);

    Subject<std::string> stringSubject;
    auto stringConsoleObserver = std::make_shared<ConsoleObserver<std::string>>();
    auto stringLoggingObserver = std::make_shared<LoggingObserver<std::string>>("string.txt");

    stringSubject.attach(stringConsoleObserver);
    stringSubject.attach(stringLoggingObserver);

    stringSubject.notify("oop");

    Subject<CustomEvent> customEventSubject;
    auto customEventConsoleObserver = std::make_shared<ConsoleObserver<CustomEvent>>();
    auto customEventLoggingObserver = std::make_shared<LoggingObserver<CustomEvent>>("custom_event.txt");

    customEventSubject.attach(customEventConsoleObserver);
    customEventSubject.attach(customEventLoggingObserver);

    customEventSubject.detach(customEventLoggingObserver);
    customEventSubject.detach(customEventConsoleObserver);
    
    CustomEvent event1 = {"555", "oop"};
    customEventSubject.notify(event1);


    return 0;
}
