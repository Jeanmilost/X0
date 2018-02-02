/*****************************************************************************
 * ==> E_Exception ----------------------------------------------------------*
 * ***************************************************************************
 * Description : Engine exception class                                      *
 * Developer   : Jean-Milost Reymond                                         *
 *****************************************************************************/

#ifndef E_EXCEPTION_H
#define E_EXCEPTION_H
#include <exception>
#include <string>

#define M_THROW_EXCEPTION(message) throw E_Exception(message, __FILE__, __FUNCTION__, __LINE__)
#define M_FORMAT_EXCEPTION(type, message) E_ExceptionFormatter::Format(type, message, __FILE__,\
        __FUNCTION__, __LINE__)
#define M_FORMAT_EXCEPTION_HTML(type, message) E_ExceptionFormatter::Format_HTML(type, message,\
        __FILE__, __FUNCTION__, __LINE__)
#define M_FORMAT_EXCEPTION_HTML_PRIVATE(type, message) E_ExceptionFormatter::Format_HTML_Private(type, message,\
        __FILE__, __FUNCTION__, __LINE__)
#define M_FORMAT_MESSAGE(message) E_ExceptionFormatter::Message(message, __FUNCTION__, __LINE__)
#define M_FORMAT_MESSAGE_HTML(message) E_ExceptionFormatter::Message_HTML(message, __FUNCTION__, __LINE__)
#define M_ASSERT(condition) {if (!condition) M_THROW_EXCEPTION("Assertion failed");}

/**
* Tool to format exceptions
*@author Jean-Milost Reymond
*/
class E_ExceptionFormatter
{
    public:
        /**
        * Formats exception message for logs
        *@param type - type of exception (STD, E_Exception, ...)
        *@param message - message to format
        *@param file - the name of the file where the exception was raised
        *@param function - the name of the function where the exception was raised
        *@param line - the line number where the excption was raised
        */
        static std::string Format(const std::string& type,
                                  const std::string& message,
                                  const std::string& file,
                                  const std::string& function,
                                  unsigned           line);

        /**
        * Formats exception message for HTML logs
        *@param type - type of exception (STD, E_Exception, ...)
        *@param message - message to format
        *@param file - the name of the file where the exception was raised
        *@param function - the name of the function where the exception was raised
        *@param line - the line number where the excption was raised
        */
        static std::string Format_HTML(const std::string& type,
                                       const std::string& message,
                                       const std::string& file,
                                       const std::string& function,
                                       unsigned           line);

        /**
        * Formats exception message for HTML logs, hiding sensitive data
        *@param type - type of exception (STD, E_Exception, ...)
        *@param message - message to format
        *@param file - the name of the file where the exception was raised
        *@param function - the name of the function where the exception was raised
        *@param line - the line number where the excption was raised
        */
        static std::string Format_HTML_Private(const std::string& type,
                                               const std::string& message,
                                               const std::string& file,
                                               const std::string& function,
                                               unsigned           line);

        /**
        * Formats a message to display to user
        *@param message - message to format
        *@param function - the name of the function where the exception was raised
        *@param line - the line number where the excption was raised
        *@returns formatted message
        */
        static std::string Message(const std::string& message,
                                   const std::string& function,
                                   unsigned           line);

        /**
        * Formats a message to display to user for HTML
        *@param message - message to format
        *@param function - the name of the function where the exception was raised
        *@param line - the line number where the excption was raised
        *@returns formatted message
        */
        static std::string Message_HTML(const std::string& message,
                                        const std::string& function,
                                        unsigned           line);
};

/**
* Exception class
*@author Jean-Milost Reymond
*/
class E_Exception : public std::exception
{
    public:
        /**
        * Constructor
        */
        E_Exception() throw();

        /**
        * Constructor
        *@param message - exception message
        */
        E_Exception(const std::string& message,
                    const std::string& file,
                    const std::string& function,
                    unsigned           line) throw();

        /**
        * Destructor
        */
        virtual ~E_Exception() throw();

        /**
        * Gets defaut exception error message
        *@returns default exception error message
        */
        virtual const char* what() const throw();

        /**
        * Formats exception text
        *@returns formatted text
        */
        virtual const char* Format() const;

        /**
        * Formats exception text for HTML
        *@returns formatted text
        */
        virtual const char* Format_HTML() const;

        /**
        * Formats exception text for HTML, hiding sensitive data
        *@returns formatted text
        */
        virtual const char* Format_HTML_Private() const;

        /**
        * Gets exception message
        *@returns exception message
        */
        virtual const std::string& Message() const;

    private:
        std::string m_FormattedMessage;
        std::string m_Message;
        std::string m_File;
        std::string m_Function;
        unsigned    m_Line;
};
#endif // E_EXCEPTION_H
