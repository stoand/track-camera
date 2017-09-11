#include "webm_parser_glue.h"

namespace webm_parser_glue {

    int parse_webm_bytes() {
        return 12342;
    };

}

// using namespace webm;

// class MyCallback : public Callback
// {
//   public:
//     Status OnElementBegin(const ElementMetadata &metadata,
//                                              Action *action) override
//     {
//         std::cout << "Element ID = 0x"
//                   << std::hex << static_cast<std::uint32_t>(metadata.id);
//         std::cout << std::dec; // Reset to decimal mode.
//         std::cout << " at position ";
//         if (metadata.position == kUnknownElementPosition)
//         {
//             // The position will only be unknown if we've done a seek. But since we
//             // aren't seeking in this demo, this will never be the case. However, this
//             // if-statement is included for completeness.
//             std::cout << "<unknown>";
//         }
//         else
//         {
//             std::cout << metadata.position;
//         }
//         std::cout << " with header size ";
//         if (metadata.header_size == kUnknownHeaderSize)
//         {
//             // The header size will only be unknown if we've done a seek. But since we
//             // aren't seeking in this demo, this will never be the case. However, this
//             // if-statement is included for completeness.
//             std::cout << "<unknown>";
//         }
//         else
//         {
//             std::cout << metadata.header_size;
//         }
//         std::cout << " and body size ";
//         if (metadata.size == kUnknownElementSize)
//         {
//             // WebM master elements may have an unknown size, though this is rare.
//             std::cout << "<unknown>";
//         }
//         else
//         {
//             std::cout << metadata.size;
//         }
//         std::cout << '\n';

//         *action = Action::kRead;
//         return Status(Status::kOkCompleted);
//     }
// };

// int main()
// {
//     MyCallback callback;
//     FileReader reader(std::freopen(nullptr, "rb", stdin));
//     WebmParser parser;
//     Status status = parser.Feed(&callback, &reader);
//     if (status.completed_ok())
//     {
//         std::cout << "Parsing successfully completed\n";
//     }
//     else
//     {
//         std::cout << "Parsing failed with status code: " << status.code << '\n';
//     }
// }