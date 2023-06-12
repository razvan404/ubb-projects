import React, { useEffect, useState } from 'react';
import { Paper, Typography, TextField, Button, FormGroup, Collapse } from '@material-ui/core';
import { Alert } from '@material-ui/lab';
import { useNavigate } from "react-router-dom";

export default function LoginPage() {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState('');
  const [usernameError, setUsernameError] = useState('');
  const [passwordError, setPasswordError] = useState('');

  const navigate = useNavigate();
  useEffect( () => {
    (async () => {
      await fetch('/api/employee-credentials')
        .then((response) => {
          if (response.ok) {
            navigate('/', {replace: true});
          }
        })
    })();
  }, []);

  const handleSubmit = (ev) => {
    ev.preventDefault();
    if (password === '' || username === '') {
      if (username === '') {
        setUsernameError('Please enter an username!');
      }
      if (password === '') {
        setPasswordError('Please enter a password!');
      }
      return;
    }

    const requestOptions = {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({
            username: username,
            password: password
        })
    }

    fetch('/api/employee-credentials', requestOptions)
      .then((response) => {
        if (!response.ok) {
          setError('Invalid credentials');
        }
        else {
            navigate('/', {replace: true});
        }
      });
  }

  return (
      <div className='loginRoot'>
        <Paper className='loginPaper' elevation={10} align='center'>
          <Typography variant='h4'>
            Bug Tracking System
          </Typography>
          <Typography color='textSecondary' variant='h5' gutterBottom>
            Login
          </Typography>
          <FormGroup className='loginForm'>
            <TextField
              label='Username'
              type='text'
              variant='outlined'
              size='small'
              onChange={(ev) => {
                setUsername(ev.target.value);
                setUsernameError('');
                setError('');
              }}
              error={usernameError !== ''}
              helperText={usernameError}
            />
            <TextField
              label='Password'
              type='password'
              variant='outlined'
              size='small'
              onChange={(ev) => {
                setPassword(ev.target.value);
                setPasswordError('');
                setError('');
              }}
              error={passwordError !== ''}
              helperText={passwordError}
            />
            <Button
                variant='contained'
                color='primary'
                className='loginSubmitButton'
                type='submit'
                onClick={handleSubmit}
            >
              Login
            </Button>
          </FormGroup>
          <Collapse in={error !== ''}>
            <Alert severity='error' onClose={() => {
              setError('');
            }}>
              {error}
            </Alert>
          </Collapse>
        </Paper>
      </div>
  );
}