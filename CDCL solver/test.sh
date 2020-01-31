echo -e "\x1B[33mLaunching tests ..."
for file in tests/*
do
    ./"$file"
done
echo -e "\x1B[33mTests finished\033[0m"
