#include "external_functions.h"




std::string voice_transfer(std::string path)
{
    // QApplication a(argc, argv);
    // Widget w;
    // w.show();
    // return a.exec();

    // 创建一个配置对象
    ps_config_t *config = ps_config_init(NULL);
    ps_config_set_str(config, "hmm", "E:\\pocketsphinx-master\\pocketsphinx_library\\pocketsphinx\\model\\en-us\\en-us");
    ps_config_set_str(config, "lm", "E:\\pocketsphinx-master\\pocketsphinx_library\\pocketsphinx\\model\\en-us\\en-us.lm.bin");
    ps_config_set_str(config, "dict", "E:\\pocketsphinx-master\\pocketsphinx_library\\pocketsphinx\\model\\en-us\\cmudict-en-us.dict");

    ps_decoder_t *ps = ps_init(config);

    // 初始化解码器
    // if (ps_start_utt(ps) < 0)
    // {
    //     std::cout << "Error initializing decoder." << std::endl;
    //     return 1;
    // }
    // 读取音频数据并进行解码
    const char *audio_data = path.c_str(); // 替换为你的音频文件路径
    FILE *audio_file = fopen(audio_data, "rb");
    if (audio_file == NULL)
    {
        std::string str="Error opening audio file.\n";
        qDebug() << str;
        return str;
    }

    ps_start_utt(ps);

    while (!feof(audio_file))
    {
        int16_t buf[512];
        size_t nread = fread(buf, sizeof(int16_t), 512, audio_file);
        ps_process_raw(ps, buf, nread, FALSE, FALSE);
    }
    // 结束解码
    ps_end_utt(ps);
    // 获取识别结果
    char const *hyp = ps_get_hyp(ps, NULL);
    std::string str=hyp;
    if (hyp != NULL)
    {
        qDebug() << "result:" << hyp << "\n";
    }
    else
    {
        qDebug() << "No key word.\n" ;
    }
    // 释放资源
    fclose(audio_file);
    ps_free(ps);
    ps_config_free(config);
    return str;

}
