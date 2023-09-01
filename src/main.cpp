#include "../lib/server.hpp"
#include "../executelib/executelib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <string>

std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Dosya açılamadı: " << filename << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));

    file.close();
    return content;
}


std::string desktopInfo(client cliData)
{
    std::string fileContent = "bash ./bash/desktop.sh " + cliData.queryString;

    fileContent = ft_system((char *)fileContent.c_str());

    return (fileContent);
}

std::string desktophtml(client cliData)
{
    std::string fileContent = readFileToString("./html/index.html");
    return (fileContent);
}

std::string cleanCache(client cliData)
{

    ft_system("bash ./bash/temizle.sh");
    return ("success");
}

void yazDosyaya(const std::string& dosyaAdi, const std::string& yazilacakMetin) {
    // Dosya açma işlemi
    std::ofstream dosya(dosyaAdi);

    // Dosya açma başarısız olduysa hata mesajı ver
    if (!dosya) {
        std::cerr << "Dosya açma hatası!" << std::endl;
        return;
    }

    // Dosyaya metni yaz
    dosya << yazilacakMetin;

    // Dosyayı kapat
    dosya.close();
}

std::string compileC(client cliData)
{
    std::string cfile = "/tmp/online.c > ' " + cliData.postVal + "'";


    yazDosyaya("online.c", cliData.postVal);

    ft_system("gcc online.c -o online");
    cfile = ft_system("./online");

    return (cfile);
}

int main()
{
    server mysw;

    mysw.handleGet("/desktop", desktophtml);
    mysw.handleGet("/desktopinfo", desktopInfo);


    mysw.handlePost("/cleanCache", cleanCache);
    mysw.handlePost("/compileC", compileC);




    mysw.createServer(2626);
}