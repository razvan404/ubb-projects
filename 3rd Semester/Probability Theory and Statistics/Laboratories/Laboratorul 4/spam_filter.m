function spam_filter(email)
  fd = fopen('keywords_ham.txt', 'r');
  ham_vector = textscan(fd, '%s');
  fclose(fd);


  fd = fopen('keywords_spam.txt', 'r');
  spam_vector = textscan(fd, '%s');
  fclose(fd);

  fd = fopen('email.txt', 'r');
  email_vector = textscan(fd, '%s');
  fclose(fd);

  spam_size = size(spam_vector{1})(1);
  ham_size = size(ham_vector{1})(1);

  words = union(spam_vector{1}, ham_vector{1});
  words_size = rows(words);
  email = unique(email_vector{1});

  PCspam = spam_size / (spam_size + ham_size);
  PCham = ham_size / (spam_size + ham_size);

  words_in_email = zeros(words_size, 1);
  for i=1:words_size
    words_in_email(i) = ismember(words(i), email);
  endfor

  words_probs_spam = zeros(words_size, 1);
  words_probs_ham = zeros(words_size, 1);
  for i=1:words_size
    words_probs_spam(i) = sum(strcmp(words(i), spam_vector{1})) / spam_size;
    words_probs_ham(i) = sum(strcmp(words(i), spam_vector{1})) / ham_size;
  endfor

  spam_probs = zeros(words_size, 1);
  ham_probs = zeros(words_size, 1);

  email_is_spam = PCspam;
  email_is_ham = PCham;

  for i=1:words_size
    if words_in_email(i) == 1
      email_is_spam *= words_probs_spam(i);
      email_is_ham *= words_probs_ham(i);
    else
      email_is_spam *= 1 - words_probs_spam(i);
      email_is_ham *= 1 - words_probs_ham(i);
    endif
  endfor

  disp(email_is_spam)
  disp(email_is_ham)

endfunction
