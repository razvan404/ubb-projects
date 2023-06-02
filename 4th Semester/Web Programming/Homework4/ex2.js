const setOkStyle = (input) => {
    input.className = 'ok-input';
}
const validateName = (name) => {
    if (name.length < 3) {
        return 'The length of the name should be bigger than 3 characters!';
    }
    else if (name.length > 52) {
        return 'The length of the name should be less than 52 characters!';
    }
    return '';
}
const validateBirthDate = (date) => {
    if (date === '') {
        return 'The birth date should not be empty!';
    }
    return '';
}
const validateAge = (age) => {
    if (age === '') {
        return 'The age should not be empty!'
    }
    if (isNaN(age)) {
        return 'The age should be a number!';
    }
    return '';
}
const validateMail = (mail) => {
    const regex = /\S+@\S+\.\S+/;
    if (mail === '') {
        return 'The mail address should not be empty!';
    }
    if (!mail.match(regex)) {
        return 'The mail address is invalid!';
    }
    return '';
}
const handleFormButtonPressed = () => {
    const nameInput = document.getElementById('nameInput');
    const birthInput = document.getElementById('birthInput');
    const ageInput = document.getElementById('ageInput');
    const mailInput = document.getElementById('mailInput');

    const inputValidators = {
        name: {
            input: nameInput,
            validator: validateName
        },
        birth: {
            input: birthInput,
            validator: validateBirthDate
        },
        age: {
            input: ageInput,
            validator: validateAge
        },
        mail: {
            input: mailInput,
            validator: validateMail
        }
    }

    let errors = '';
    let err;

    for (const key in inputValidators) {
        const inputValidator = inputValidators[key];
        if ((err = inputValidator.validator(inputValidator.input.value)) !== '') {
            errors += err + '\n';
            inputValidator.input.className = 'invalid-input';
        }
    }

    if (errors !== '') {
        errors.slice(0, -1);
        alert(errors);
    }
    else {
        alert('Input is valid!');
    }
}