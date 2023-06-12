import React, { useEffect, useState } from 'react';
import { tableIcons } from "./Utils";
import MaterialTable from "material-table";
import { Button, ButtonGroup, Collapse, Typography } from "@material-ui/core";
import { Alert } from "@material-ui/lab";

export default function AssignedBugsPage() {
    const [successMsg, setSuccessMsg] = useState('');
    const [errorMsg, setErrorMsg] = useState('');

    const [bugs, setBugs] = useState([]);
    const loadBugs = () => {
        fetch('/api/programmer-bugs')
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
            {title: 'Status', field: 'status', hidden: true },
            {title: 'Created at', field: 'created_at', hidden: true},
            {title: 'Reporter', field: 'reporter'},
            {title: 'Solver', field: 'solver', hidden: true}
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
                        return;
                    }
                    setSelectedRow(currentSelectedRow);
                }}
                options={{
                    rowStyle: (rowData) => ({
                        backgroundColor: selectedRow === rowData ? "#5972FF" : "#FFF",
                    })
            }}
            />
        );
    }

    const handleMarkBugAsFixed = () => {
        if (selectedRow === null) {
            setErrorMsg('Please select a bug');
            return;
        }
        if (!confirm('Are you sure you want to mark this bug as fixed?')) {
            return;
        }
        const requestOptions = {
            method: 'PATCH',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                status: 'fixed'
                })
            }
        fetch(`/api/programmer-bugs/${selectedRow.id}`, requestOptions)
            .then((response) => {
                if (!response.ok) {
                    response.json().then((data) => setSuccessMsg(data.error));
                }
                else {
                    response.json().then((data) => setSuccessMsg(data.msg));
                    loadBugs();
                }
            });
    }

    const handleMarkBugAsUnassigned = () => {
        if (selectedRow === null) {
            setErrorMsg('Please select a bug');
            return;
        }
        if (!confirm('Are you sure you want to mark this bug as unassigned?')) {
            return;
        }
        const requestOptions = {
            method: 'PATCH',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                status: 'unassigned'
            })
        }
        fetch(`/api/programmer-bugs/${selectedRow.id}`, requestOptions)
            .then((response) => {
                if (!response.ok) {
                    response.json().then((data) => setSuccessMsg(data.error));
                }
                else {
                    response.json().then((data) => setSuccessMsg(data.msg));
                    loadBugs();
                }
            });
    }

    return ( <>
            <Typography variant="h4">
              Your Assignments
            </Typography>

            <ButtonGroup fullWidth className='gap-20'>
              <Button
                  variant='contained'
                  color='primary'
                  onClick={handleMarkBugAsFixed}
                  disabled={selectedRow === null}>
                Mark Bug as Fixed
              </Button>
              <Button
                  variant='contained'
                  color='secondary'
                  onClick={handleMarkBugAsUnassigned}
                  disabled={selectedRow === null}
              >
                Mark Bug as Unassigned
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

            <div>
                {getBugsTable()}
            </div>
        </>
    );
}