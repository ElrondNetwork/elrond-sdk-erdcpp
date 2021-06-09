#ifndef ARGHANDLER_H
#define ARGHANDLER_H

#include <string>
#include <vector>
#include <map>

#include "utils/errors.h"

namespace ih
{
enum RequestType
{
    invalid,
    help,
    loadPemFile,
    createSignedTransactionWithPemFile
};

class RequestedCmd
{
public:
    RequestedCmd(std::map<uint32_t, std::string> const &userInputs,
                 RequestType const &reqType, errorCode const &errCode);

    const std::map<uint32_t, std::string> &getUserInputs() const;

    const RequestType &getRequestType() const;

    const errorCode &getErrorCode() const;

private:
    std::map<uint32_t, std::string> const m_userInputs;
    RequestType const m_requestType;
    errorCode const m_errCode;
};

class ArgHandler
{
public:

    explicit ArgHandler(int const &argc, char *const argv[]);

    RequestedCmd getRequestedCmd();

private:

    unsigned long argCount() const;

    bool isCmdGroup(std::string const &arg) const;

    bool isSubCmd(uint32_t subCmdIdx, std::string const &subCmd) const;

    template<typename T>
    bool checkAndSetUserInput(uint32_t const &argIdx, std::string const &arg,
                              std::map<uint32_t, std::string> &userInputs, uint32_t userInputIdx,
                              errorCode errCode);

    std::vector<std::string> m_arguments;
    errorCode m_errCode;
};
}


#endif // !ARGHANDLER_H