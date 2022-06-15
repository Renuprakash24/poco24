#ifndef DLTCHANNEL_H
#define DLTCHANNEL_H

#include "Poco/Channel.h"
#include "Poco/Timer.h"
#include <ostream>
#include <dlt.h>
#include <map>
#include "Message.h"
#include <atomic>


namespace Poco {

class Foundation_API DLTChannel : public Channel
{
public:
    DLTChannel();

    void open();

    void close();

    void log(const Message& msg);

    void setProperty(const std::string& name, const std::string& value);

    std::string getProperty(const std::string& name) const;

    void checkLoggingStatus(Timer& timer);

    static const std::string PROP_APPID;
protected:
    ~DLTChannel();
private:
    bool _open;
    std::atomic_bool _logged;
    std::string _appID;
    std::ostream& _str;
    typedef std::map<std::string, DltContext*> DLTContextMap;  // map of ContextID, DltContext
    DLTContextMap* _pDltContextMap;
    typedef std::map<Message::Priority, DltLogLevelType> DLTLogLevelMapType;
    DLTLogLevelMapType _DLTLogLevelMap;

    // Returns the DltContext instance for the given ContextID
    DltContext* fetchDltContext(const std::string &ctxID);

    // From the given name, decides if this name is an actual Context ID, or the domanin bundle name
    // based on rule that the name contains '.' characters
    // If contextID:  automatically strips the name to four chars and returns it
    // If domanin bundle name: setup the default Context ID "AFW" and returns it
    std::string setupContext(std::string name);

};

} // namespace Poco

#endif // DLTCHANNEL_H
