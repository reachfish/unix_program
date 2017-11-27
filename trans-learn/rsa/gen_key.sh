#test.key包含公钥和私钥
openssl genrsa -out test.key 1024

#从中提取私钥
openssl rsa -in test.key -pubout -out test_pub.key

