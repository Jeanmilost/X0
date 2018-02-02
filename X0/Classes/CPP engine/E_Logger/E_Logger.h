/******************************************************************************
 * ==> E_Logger --------------------------------------------------------------*
 ******************************************************************************
 * Description : Base class for logging                                       *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#ifndef E_Logger_h
#define E_Logger_h

#include <sstream>

/**
* Basic logging class
*@author Jean-Milost Reymond
*/
class E_Logger
{
    public:
        E_Logger();
        virtual ~E_Logger();

        /**
        * Operator <<
        *@param argument - argument to log
        *@returns itself
        */
        virtual E_Logger& operator << (const char* argument);
        virtual E_Logger& operator << (const wchar_t* argument);
        virtual E_Logger& operator << (const std::string& argument);
        virtual E_Logger& operator << (const std::wstring& argument);
        virtual E_Logger& operator << (char argument);
        virtual E_Logger& operator << (wchar_t argument);
        virtual E_Logger& operator << (short argument);
        virtual E_Logger& operator << (unsigned short argument);
        virtual E_Logger& operator << (int argument);
        virtual E_Logger& operator << (unsigned argument);
        virtual E_Logger& operator << (const long& argument);
        virtual E_Logger& operator << (const unsigned long& argument);
        virtual E_Logger& operator << (const long long& argument);
        virtual E_Logger& operator << (const unsigned long long& argument);
        virtual E_Logger& operator << (const float& argument);
        virtual E_Logger& operator << (const double& argument);

        /**
        * Opens logger
        *@param fileName - log file name
        */
        virtual void Open(const std::wstring& fileName);

        /**
        * Checks if logger is open
        *@returns true if logger is open, otherwise false
        */
        virtual bool IsOpen();

        /**
        * Closes logger
        *@param save - if true, file will be saved on disk
        */
        virtual void Close(bool save);

        /**
        * Clears log content
        */
        virtual void Clear();

        /**
        * Gets log file name
        *@returns file name
        */
        virtual std::wstring GetFileName();

        /**
        * Gets log content
        *@returns content
        */
        virtual std::wstring GetContent();

        /**
        * Gets information log line start
        *@returns line start
        */
        virtual std::wstring BeginInfo() = 0;

        /**
        * Gets information log line end
        *@returns line end
        */
        virtual std::wstring EndInfo() = 0;

        /**
        * Gets warning log line start
        *@returns line start
        */
        virtual std::wstring BeginWarn() = 0;

        /**
        * Gets warning log line end
        *@returns line end
        */
        virtual std::wstring EndWarn() = 0;

        /**
        * Gets error log line start
        *@returns line start
        */
        virtual std::wstring BeginError() = 0;

        /**
        * Gets error log line end
        *@returns line end
        */
        virtual std::wstring EndError() = 0;

        /**
        * Gets date
        *@returns date
        */
        virtual std::wstring GetDate();

        /**
        * Gets time
        *@returns time
        */
        virtual std::wstring GetTime();

        /**
        * Gets date and time
        *@returns date and time
        */
        virtual std::wstring GetDateTime();

        /**
        * Gets end line
        *@returns end line
        */
        virtual std::wstring EndLine();

    protected:
        std::auto_ptr<std::wostringstream> m_pStream;

    private:
        std::wstring m_FileName;

        /**
        * Save log to file
        *@returns true on success, otherwise false
        */
        bool Save();
};

#endif
