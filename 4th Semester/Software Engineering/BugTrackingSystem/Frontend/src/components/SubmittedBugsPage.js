import React, { useEffect, useState } from 'react';
import { renderStatus, tableIcons } from "./Utils";
import MaterialTable from "material-table";
import {
    Button,
    ButtonGroup,
    Collapse,
    FormControl,
    TextField,
    Typography,
} from "@material-ui/core";
import {Alert} from "@material-ui/lab";

export default function SubmittedBugsPage() {
    const [title, setTitle] = useState('');
    const [titleError, setTitleError] = useState('');
    const [description, setDescription] = useState('');
    const [descriptionError, setDescriptionError] = useState('');

    const [successMsg, setSuccessMsg] = useState('');
    const [errorMsg, setErrorMsg] = useState('');

    const [bugs, setBugs] = useState([]);
    const loadBugs = () => {
        fetch('/api/tester-bugs')
            .then((response) => response.json())
            .then((data) => {
                setBugs(data);
            });
    }
    useEffect(() => {
        loadBugs();
    }, []);


    const [selectedRow, setSelectedRow] = useState(null);
    const getBugsTable = () => {
        const columns = [
            {title: 'ID', field: 'id', defaultSort: 'desc'},
            {title: 'Title', field: 'title'},
            {title: 'Description', field: 'description'},
            {title: 'Status', field: 'status', render: rowData => renderStatus(rowData.status) },
            {title: 'Created at', field: 'created_at', hidden: true},
            {title: 'Reporter', field: 'reporter', hidden: true},
            {title: 'Solver', field: 'solver'}
        ];

        return (
            <MaterialTable
                title='Submitted Bugs'
                columns={columns}
                data={bugs}
                icons={tableIcons}
                onRowClick={(evt, currentSelectedRow) => {
                    if (selectedRow === currentSelectedRow) {
                        setSelectedRow(null);
                        setTitle('');
                        setDescription('');
                        return;
                    }
                    setSelectedRow(currentSelectedRow);
                    setTitle(currentSelectedRow.title);
                    setDescription(currentSelectedRow.description);
                }}
                options={{
                    rowStyle: (rowData) => ({
                        backgroundColor: selectedRow === rowData ? "#5972FF" : "#FFF",
                    })
            }}
            />
        );
    }

    const validateInput = () => {
        let isValid = true;
        if (title.length < 3 || title.length > 32) {
            setTitleError('Title must be between 3 and 32 characters');
            isValid = false;
        }
        if (description.length < 3 || description.length > 256) {
            setDescriptionError('Description must be between 3 and 256 characters');
            isValid = false;
        }
        return isValid;
    }

    const handleBugReport = () => {
        if (!validateInput()) {
            return;
        }
        if (!confirm('Are you sure you want to report this bug?')) {
            return;
        }
        const requestOptions = {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                title: title,
                description: description,
            })
        }
        fetch('/api/tester-bugs', requestOptions)
            .then((response) => {
                if (!response.ok) {
                    response.json().then((data) => setErrorMsg(data.error));
                }
                else {
                    response.json().then((data) => setSuccessMsg(data.msg));
                    loadBugs();
                    setSelectedRow(null);
                    setTitle('');
                    setDescription('');
                }
            });
    }

    const handleBugUpdate = () => {
        if (selectedRow === null) {
            setErrorMsg('Please select a bug to update');
            return;
        }
        if (!validateInput()) {
            return;
        }
        if (!confirm('Are you sure you want to update this bug?')) {
            return;
        }
        const requestOptions = {
            method: 'PATCH',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                title: title,
                description: description,
            })
        }
        fetch(`/api/tester-bugs/${selectedRow.id}`, requestOptions)
            .then((response) => {
                if (!response.ok) {
                    response.json().then((data) => setErrorMsg(data.error));
                }
                else {
                    response.json().then((data) => setSuccessMsg(data.msg));
                    loadBugs();
                    setSelectedRow(null);
                }
            });
    }

    const handleBugRemove = () => {
        if (selectedRow === null) {
            setErrorMsg('Please select a bug to remove');
            return;
        }
        if (!validateInput()) {
            return;
        }
        if (!confirm('Are you sure you want to remove this bug?')) {
            return;
        }
        const requestOptions = {
            method: 'DELETE',
            headers: {
                'Content-Type': 'application/json',
            }
        }
        fetch(`/api/tester-bugs/${selectedRow.id}`, requestOptions)
            .then((response) => {
                if (!response.ok) {
                    response.json().then((data) => setErrorMsg(data.error));
                }
                else {
                    response.json().then((data) => setSuccessMsg(data.msg));
                    loadBugs();
                    setSelectedRow(null);
                }
            });
    }

    return ( <>
            <Typography variant="h4">
              Submitted Bugs
            </Typography>

            <FormControl fullWidth margin='normal'>
              <TextField
                  label='Title'
                  value={title}
                  onChange={(ev) => {
                      setTitle(ev.target.value);
                      setTitleError('');
                  }}
                  error={titleError !== ''}
                  helperText={titleError}
              />
              <TextField
                  label='Description'
                  value={description}
                  onChange={(ev) => {
                      setDescription(ev.target.value);
                      setDescriptionError('');
                  }}
                  error={descriptionError !== ''}
                  helperText={descriptionError}
                  multiline
                  maxRows={4}
              />
            </FormControl>

            <ButtonGroup fullWidth className='gap-20'>
              <Button
                  variant="contained"
                  color="primary"
                  onClick={handleBugReport}>
                Report Bug
              </Button>
              <Button
                  variant="contained"
                  color="primary"
                  onClick={handleBugUpdate}
                  disabled={selectedRow === null || selectedRow.status !== 'unassigned'}
              >
                Update Bug
              </Button>
              <Button
                  variant="contained"
                  color="secondary"
                  onClick={handleBugRemove}
                  disabled={selectedRow === null || selectedRow.status !== 'unassigned'}>
                Remove Bug
              </Button>
            </ButtonGroup>

            <Collapse in={successMsg !== '' || errorMsg !== ''}>
                <Alert severity={successMsg !== '' ? 'success' : 'error'} onClose={ () => {
                    setErrorMsg('');
                    setSuccessMsg('');
                    }}>
                    {successMsg !== '' ? successMsg : errorMsg}
                </Alert>
            </Collapse>
            {getBugsTable()}
        </>
    );
}