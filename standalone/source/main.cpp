#include <NovaLLM/NovaLLM-cpp.h>
#include <NovaLLM/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main(int argc, char** argv) -> int {
  const std::unordered_map<std::string, nova_llm::LanguageCode> languages {
      {"en", nova_llm::LanguageCode::EN},
      {"de", nova_llm::LanguageCode::DE},
      {"es", nova_llm::LanguageCode::ES},
      {"fr", nova_llm::LanguageCode::FR},
  };

  cxxopts::Options options(*argv, "A program to welcome the world!");

  std::string language;
  std::string name;

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "NovaLLM, version " << NOVA_LLM_VERSION << std::endl;
    return 0;
  }

  auto langIt = languages.find(language);
  if (langIt == languages.end()) {
    std::cerr << "unknown language code: " << language << std::endl;
    return 1;
  }

  nova_llm::NovaLLM nova_llm(name);
  std::cout << nova_llm.greet(langIt->second) << std::endl;

  return 0;
}
