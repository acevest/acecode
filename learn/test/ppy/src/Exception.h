/*
 *--------------------------------------------------------------------------
 *   File Name:	Exception.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Mar 24 11:13:21 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PPY_EXCEPTION_H
#define	_PPY_EXCEPTION_H

#include <exception>
#include <string>
#include <cstring>
#include <sstream>
#include <cerrno>

namespace ppy {

class Exception : public std::exception {
public:
	enum ExceptionCode {
		UNKNOWN = 0,
		LOGIC,
		INVARG,
		INTERNAL,
		GENERIC,
		MAXEXPTCODE // Don't Use it...
	};


	~Exception() throw() {}

	Exception(	Exception::ExceptionCode exptcode,
			const std::string& desc,
			const std::string& src,
			const char *file,
			int line
			);

	Exception(const Exception& e);

	void operator = (const Exception& e);

	virtual const std::string& getDetail() const;

	virtual inline int getExceptionCode() const {
		return m_ExceptionCode;
	}

	virtual inline const std::string& getSource() const {
		return m_Source;
	}

	virtual inline const std::string& getFile() const {
		return m_File;
	}

	virtual inline int getLine() const {
		return m_Line;
	}
	

protected:

	static const std::string ExceptionMessage[];

	Exception::ExceptionCode	m_ExceptionCode;
	std::string		m_Description;
	std::string		m_Source;
	std::string		m_File;
	mutable std::string	m_Detail;
	int			m_Line;
};




class UnknownException : public Exception {
public:
	UnknownException(const std::string& desc, const std::string& src,
			const char *file, int line)
	: Exception(Exception::UNKNOWN, desc, src, file, line) {}
};

class LogicException : public Exception {
public:
	LogicException(	const std::string& desc, const std::string& src,
			const char *file, int line)
	: Exception(Exception::LOGIC, desc, src, file, line) {}
};

class InvArgException : public Exception {
public:
	InvArgException(const std::string& desc, const std::string& src,
			const char *file, int line)
	: Exception(Exception::INVARG, desc, src, file, line) {}
};

class InternalException : public Exception {
public:
	InternalException(const std::string& desc, const std::string& src,
			  const char *file, int line)
	: Exception(Exception::INTERNAL, desc, src, file, line) {}
};

class GenericException : public Exception {
public:
/*
	GenericException(const std::string& desc, const std::string& src,
			  const char *file, int line)
	: Exception(Exception::GENERIC, desc, src, file, line),
	  m_Errno(errno) {}
*/
	GenericException(const std::string& desc, const std::string& src,
			  const char *file, int line, int eno)
	: Exception(Exception::GENERIC, desc, src, file, line),
	  m_Errno(eno) {}


	inline int getErrno() const;

	virtual const std::string& getDetail() const;

protected:
	int m_Errno;
};

template <int T>
struct ExceptionCodeType {
	enum {
		ExceptionCode = T
	};
};

class ExceptionFactory {
private:
	ExceptionFactory() {}
public:
	static UnknownException 
	create(	ExceptionCodeType<Exception::UNKNOWN>,
		const std::string& desc,
		const std::string& src,
		const char *file,
		int line)
	{
		return UnknownException(desc, src, file, line);
	}

	static LogicException
	create(	ExceptionCodeType<Exception::LOGIC>,
		const std::string& desc,
		const std::string& src,
		const char *file,
		int line)
	{
		return LogicException(desc, src, file, line);
	}

	static InvArgException
	create(	ExceptionCodeType<Exception::INVARG>,
		const std::string& desc,
		const std::string& src,
		const char *file,
		int line)
	{
		return InvArgException(desc, src, file, line);
	}

	static InternalException
	create(	ExceptionCodeType<Exception::INTERNAL>,
		const std::string& desc,
		const std::string& src,
		const char *file,
		int line)
	{
		return InternalException(desc, src, file, line);
	}

	static GenericException
	create(	ExceptionCodeType<Exception::GENERIC>,
		const std::string& desc,
		const std::string& src,
		const char *file,
		int line,
		int eno = errno)
	{
		return GenericException(desc, src, file, line, eno);
	}
};


#define	PPY_EXCEPT(exptcode, desc, src) throw ppy::ExceptionFactory::	\
	create(ppy::ExceptionCodeType<exptcode>(), desc, src,		\
	__FILE__, __LINE__ );

#define	PPY_GENERIC_EXCEPT(eno) throw ppy::ExceptionFactory::create	\
	(ppy::ExceptionCodeType<ppy::Exception::GENERIC>(),		\
	"failed to call lib function", __FUNCTION__, 			\
	__FILE__, __LINE__, eno);


} // end namespace ppy
#endif //_PPY_EXCEPTION_H
