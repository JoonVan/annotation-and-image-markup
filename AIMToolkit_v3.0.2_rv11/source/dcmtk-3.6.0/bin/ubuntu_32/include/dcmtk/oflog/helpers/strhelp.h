/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef LOG4CPLUS_HELPERS_STRINGHELPER_HEADER_
#define LOG4CPLUS_HELPERS_STRINGHELPER_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/ofstd/oflist.h"

//#include <algorithm>
//#include <limits>
//#include <iterator>


namespace log4cplus {
    namespace helpers {

        /**
         * Returns <code>s</code> in upper case.
         */
        LOG4CPLUS_EXPORT log4cplus::tstring toUpper(const log4cplus::tstring& s);


        /**
         * Returns <code>s</code> in lower case.
         */
        LOG4CPLUS_EXPORT log4cplus::tstring toLower(const log4cplus::tstring& s);


        /**
         * Tokenize <code>s</code> using <code>c</code> as the delimiter and
         * put the resulting tokens in <code>_result</code>.  If
         * <code>collapseTokens</code> is false, multiple adjacent delimiters
         * will result in zero length tokens.
         *
         * <b>Example:</b>
         * <pre>
         *   string s = // Set string with '.' as delimiters
         *   list<log4cplus::tstring> tokens;
         *   tokenize(s, '.', back_insert_iterator<list<string> >(tokens));
         * </pre>
         */
        template <class StringType>
        inline
        void
        tokenize(const StringType& s, typename StringType::value_type c,
            OFList<StringType>& result, bool collapseTokens = true)
        {
            typedef typename StringType::size_type size_type;
            size_type const slen = s.length();
            size_type first = 0;
            size_type i = 0;
            for (i=0; i < slen; ++i)
            {
                if (s[i] == c)
                {
                    result.push_back(StringType (s, first, i - first));
                    if (collapseTokens)
                        while (i+1 < slen && s[i+1] == c)
                            ++i;
                    first = i + 1;
                }
            }
            if (first != i)
                result.push_back(StringType (s, first, i - first));
        }


        template <typename intType>
        struct ConvertIntegerToStringHelper
        {
            static inline
            void
            step1 (tchar * & it, intType & value)
            {
                // This code assumes two-compliments'. The problem here is that
                // integer overflow of an signed type is undefined behavior :(
                // This code is based upon http://www.fefe.de/intof.html

                // True if intType is unsigned
                const OFBool isUnsigned = (OFstatic_cast(intType, -1) < 0) ? OFFalse : OFTrue;

                // If intType is a signed type, halfMaxSigned is intType_MAX / 2
                const intType halfMaxSigned = OFstatic_cast(intType, 1) << (sizeof(intType) * 8 - 2);

                // if intType is a signed type, MaxSigned is its intType_MAX
                const intType maxSigned = halfMaxSigned - 1 + halfMaxSigned;

                // if intType is a signed type, MinSigned is its intType_MIN
                const intType minSigned = OFstatic_cast(intType, -1) - maxSigned;

                // This is the minimum value that intType can represent;
                const intType minVal = isUnsigned ? 0 : minSigned;

                //if (value == (STD_NAMESPACE numeric_limits<intType>::min) ())
                if (value == minVal)
                {
                    intType const r = value / 10;
                    intType const a = (0-r) * 10;
                    intType const mod = 0-(a + value);
                    value = 0-r;

                    *(it - 1) = OFstatic_cast(tchar, LOG4CPLUS_TEXT('0') + mod);
                    --it;
                }
                else
                    value = 0-value;
            }
        };


        template<class intType>
        inline
        void
        convertIntegerToString (tstring & str, intType value)
        {
            if (value == 0)
                str = LOG4CPLUS_TEXT("0");
            // We can't use (value < 0) because that could cause a compiler
            // warning for unsigned types.
            bool const negative = !(value > 0 || value == 0);

            const size_t buffer_size = 30; // More than enough space, even for 64 bit integers
                // = intTypeLimits::digits10 + 2;
            tchar buffer[buffer_size];
            tchar * it = &buffer[buffer_size];
            tchar const * const buf_end = it;

            if (negative)
                ConvertIntegerToStringHelper<intType>::step1(it, value);

            for (; value != 0; --it)
            {
                intType mod = value % 10;
                value = value / 10;
                *(it - 1) = OFstatic_cast(tchar, LOG4CPLUS_TEXT('0') + mod);
            }

            if (negative)
            {
                --it;
                *it = LOG4CPLUS_TEXT('-');
            }

            str.assign (OFstatic_cast(tchar const *, it), buf_end - it);
        }


        template<class intType>
        inline
        tstring
        convertIntegerToString (intType value)
        {
            tstring result;
            convertIntegerToString (result, value);
            return result;
        }

    } // namespace helpers

} // namespace log4cplus

#endif // LOG4CPLUS_HELPERS_STRINGHELPER_HEADER_
