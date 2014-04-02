/*
 *--------------------------------------------------------------------------
 *   File Name:	Exception.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Mar 24 11:37:33 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include "Exception.h"

using namespace ppy;

const std::string Exception::ExceptionMessage[Exception::MAXEXPTCODE] = {
	"Unknown Exception",
	"Logic Exception",
	"Invalid Argument Exception",
	"Internal Exception",
	"Generic Exception",
};

Exception::Exception(	Exception::ExceptionCode exptcode,
			const std::string& desc,
			const std::string& src,
			const char *file,
			int line
			) :
m_ExceptionCode(exptcode),
m_Description(desc),
m_Source(src),
m_File(file),
m_Line(line)
{
	
}

Exception::Exception(const Exception& e) :
m_ExceptionCode(e.m_ExceptionCode),
m_Description(e.m_Description),
m_Source(e.m_Source),
m_File(e.m_File),
m_Line(e.m_Line)
{
}

void Exception::operator = (const Exception& e)
{
	m_ExceptionCode = e.m_ExceptionCode;
	m_Description = e.m_Description;
	m_Source = e.m_Source;
	m_File = e.m_File;
	m_Line = e.m_Line;
}

const std::string& Exception::getDetail() const {

	if(!m_Detail.empty()) return m_Detail;

	std::stringstream detail;

	detail	<< "PPY EXCEPTION(" << m_ExceptionCode << ":"
		<< Exception::ExceptionMessage[m_ExceptionCode] << "): "
		<< m_Description << " in " << m_Source
		<< " at " << m_File << ":" << m_Line;

	m_Detail = detail.str();

	return m_Detail;
}


const std::string& GenericException::getDetail() const {

	Exception::getDetail();

	std::stringstream detail;
	char buf[256];
	detail << " errno:" << m_Errno;
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
	if(strerror_r(m_Errno, buf, 256) == 0) {
		detail << ":";
	}
	m_Detail += detail.str();
	m_Detail += buf;
#else
	char *perr = strerror_r(m_Errno, buf, 256);
	if(perr != 0) {
		detail << ":";
	}
	m_Detail += detail.str();
	m_Detail += perr;
#endif
	return m_Detail;
}

int GenericException::getErrno() const {
	return m_Errno;
}
