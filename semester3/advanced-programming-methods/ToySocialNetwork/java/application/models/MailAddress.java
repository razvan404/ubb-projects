package application.models;

import application.models.exceptions.ValidationException;

public class MailAddress {
    private final String mailAddress;

    private MailAddress(String mailAddress) {
        this.mailAddress = mailAddress;
    }

    @Override
    public String toString() {
        return mailAddress;
    }

    public static MailAddress of(String mail) throws ValidationException {
        if (mail == null || mail.equals("") || mail.equalsIgnoreCase("null")) {
            throw new ValidationException("The mail must not be null");
        }
        if (mail.length() > 64) {
            throw new ValidationException("The mail address must have at most 64 characters");
        }
        if (!mail.matches("[a-zA-Z0-9_.-]+@[a-z.]+[.][a-z]+")) {
            throw new ValidationException("The mail address is invalid");
        }
        return new MailAddress(mail);
    }
}
