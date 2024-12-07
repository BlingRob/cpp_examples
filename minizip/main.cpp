/// \brief Zip reader and archiver small utility
/// \brief Library on https://github.com/richgel999/miniz/tree/master https://github.com/p-ranav/argparse

#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#include <filesystem>
#include <concepts>
#include <format>

#include <miniz.h>
#include <argparse/argparse.hpp>

enum class ArchiveTypes
{
  Reader,
  Writer
};

template<ArchiveTypes type>
class Archive
{
  public:

  /// @brief Constructor
  /// @param archiveName Name of archive
  Archive(const std::string_view archiveName):
          archiveName_{archiveName}
        , archive_{}
        , opened_{false}
  {
    constexpr auto extension{".zip"};

    if(archiveName_.rfind(extension) == std::string::npos)
    {
      archiveName_ += extension;
    }

    if constexpr (type == ArchiveTypes::Reader)
    {
      open_reader();
    }
    else
    {
      open_writer();
    }
  }

  ~Archive()
  {
    if constexpr (type == ArchiveTypes::Writer)
    {
      mz_zip_writer_finalize_archive(&archive_);
    }
    mz_zip_end(&archive_);
  }

  /// @brief Check, that archive is open
  /// @return true, if open
  bool is_open() const
  {
    return opened_;
  }

  /// @brief Getting information about archive
  /// @return strign with information about archive
  std::string get_info() requires(type == ArchiveTypes::Reader)
  {
    if(!opened_)
    {
      return "";
    }

    std::string result{std::string("Archive size: ") + std::to_string(archive_.m_archive_size) + std::string("\n") +
                       std::string("Files in archive: ") + std::to_string(archive_.m_total_files)};

    return result;
  }

  /// @brief Archiving enumerate files
  /// @param files vector of files
  /// @return true, if archived
  bool arhive_files(std::vector<std::string> files) requires(type == ArchiveTypes::Writer)
  {
    for(const auto& file: files)
    {
      std::string filename = std::filesystem::path(file).filename().string();

      std::cout << std::format("Openning file {}...", filename) << std::endl;

      std::ifstream ifile(filename);
      // Check, that file openning
      if(ifile.is_open())
      {
          std::cout << std::format("File {} was openned", filename) << std::endl;
          std::cout << std::format("File {} is archiving...", filename) << std::endl;

          // std::ostringstream sstr;
          // sstr << ifile.rdbuf();
          // mz_zip_writer_add_mem(&archive_, filename.c_str(), sstr.str().c_str(), sstr.str().size(), MZ_BEST_COMPRESSION);
          ifile.close();

           if(mz_zip_writer_add_file(&archive_, filename.c_str(), filename.c_str(), nullptr, 0, MZ_BEST_COMPRESSION))
           {
            std::cout << std::format("File {} was archived", filename) << std::endl;
           }
           else
           {
            std::cout << std::format("File {} wasn't archived", filename) << std::endl;
           }
      }
      else
      {
        std::cout << std::format("File {} wasn't openned", filename) << std::endl;
      }
    }
    
    return true;
  }

  private:

  void open_reader()
  {
    if(!std::filesystem::exists(archiveName_))
    {
      opened_ = false;
    }

    opened_ = mz_zip_reader_init_file(&archive_, archiveName_.c_str(), MZ_ZIP_FLAG_IGNORE_PATH);
  }

  void open_writer()
  {
    opened_ = mz_zip_writer_init_file(&archive_, archiveName_.c_str(), 100);
  }

  private:

  /// @brief Name of archive
  std::string archiveName_;

  /// @brief Current working archive
  mz_zip_archive archive_;

  /// @brief Open flag
  bool opened_;
};

int main(int argc, char** argv)
{
    argparse::ArgumentParser program("zip_utility");

    program.add_argument("-o", "--output")
      .help("result archive")
      .default_value(std::string())
      .nargs(1)
      .metavar("name");

    program.add_argument("-f", "--files")
      .help("file, where will archive other files")
      .nargs(argparse::nargs_pattern::at_least_one)
      .metavar("names");

    program.add_argument("-r", "--read")
      .help("archive, that will be read")
      .default_value(std::string())
      .nargs(1)
      .metavar("name");

    /// @todo Make extract from archive

    try 
    {
      program.parse_args(argc, argv);

      auto readArchiveName = program.get<std::string>("-r");
      
      if(!readArchiveName.empty())
      {
          Archive<ArchiveTypes::Reader> inputArchive("./" + readArchiveName);
          if(inputArchive.is_open())
          {
            std::cout << inputArchive.get_info() << std::endl;
          }
          else
          {
            std::cerr << "Archive wasn't openned!" << std::endl;
          }
      }
      
      auto files = program.get<std::vector<std::string>>("--files");
      auto outputArchiveName = program.get<std::string>("--output");

      if(files.size() > 0 && !outputArchiveName.empty())
      {
          Archive<ArchiveTypes::Writer> outputArchive("./" + outputArchiveName);

          if(outputArchive.is_open())
          {
            outputArchive.arhive_files(files);
          }
          else
          {
            std::cerr << "Archive wasn't openned!" << std::endl;
          }
      }
    }
    catch (const std::exception& err) 
    {
      std::cerr << err.what() << std::endl;
      std::cerr << program;
      std::exit(1);
    }

    return 0;
}