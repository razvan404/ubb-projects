import React, {useEffect} from 'react';
import {useState} from 'react';
import {Typography, FormControl, TextField, ButtonGroup, Button} from "@mui/material";
import {DateTimePicker} from "@mui/x-date-pickers-pro";
import {AddRide, DeleteRide, GetAllRides, UpdateRide} from "./utils/RestCalls";
import Ride from "./models/Ride";
import MaterialTable, {Column} from 'material-table';
import {tableIcons} from "./utils/Utils";
import {DATE_FORMAT_OPTIONS} from "./utils/Consts";

export default function RidesPage() {
    const [destination, setDestination] = useState<string>('');
    const [departure, setDeparture] = useState<Date | null>(null);

    const [destinationError, setDestinationError] = useState<string>('');
    const [departureError, setDepartureError] = useState<string>('');

    const [rides, setRides] = useState<Ride[]>([]);
    const [selectedRide, setSelectedRide] = useState<Ride>();

    useEffect(() => {
        const getRides = async () => {
            const ridesFromServer = await GetAllRides();
            setRides(ridesFromServer);
            console.log(ridesFromServer);
        }
        getRides().then(null);
    }, [])

    const handleDestinationChange = (dest: string) => {
        setDestination(dest);
        if (dest.length < 3 || dest.length > 50) {
            setDestinationError('Destination must be between 3 and 50 characters');
        } else {
            setDestinationError('');
        }
    }

    const handleDepartureChange = (date: Date | null) => {
        setDeparture(date);
        if (date === null) {
            setDepartureError('Departure is required');
        } else {
            const difference = date.getTime() - Date.now();
            const days = Math.ceil(difference / (1000 * 3600 * 24));
            if (days < 1 || days > 30) {
                setDepartureError('Departure must be between 1 and 30 days from now');
            } else {
                setDepartureError('');
            }
        }
    }

    const handleAddRide = () => {
        if (destinationError !== '' || departureError !== '' || destination === '' || departure === null) {
            window.alert('Please fill in all the fields correctly!');
            return;
        }
        if (!window.confirm('Are you sure you want to add this ride?')) {
            return;
        }
        const newRide: Ride = {
            destination: destination,
            departure: departure
        }
        AddRide(newRide).then(ride => {
            if (ride !== undefined) {
                setRides([...rides, ride]);
                setDestination('');
                setDeparture(null);
                setDestinationError('');
                setDepartureError('');
                window.alert('Ride added successfully');
            }
        });
    }

    const handleUpdateRide = () => {
        console.log(departure);
        if (selectedRide === undefined) {
            window.alert('Please select a ride to update!');
            return;
        }
        if (destinationError !== '' || departureError !== '' || destination === '' || departure === null) {
            window.alert('Please fill in all the fields correctly!');
            return;
        }
        if (!window.confirm('Are you sure you want to update this ride?')) {
            return;
        }
        const newRide: Ride = {
            id: selectedRide.id,
            destination: destination,
            departure: departure
        }
        UpdateRide(newRide).then(ride => {
            if (ride !== undefined) {
                setRides(rides.map(r => r.id === ride.id ? ride : r));
                setSelectedRide(undefined);
                setDestination('');
                setDeparture(null);
                setDestinationError('');
                setDepartureError('');
                window.alert('Ride updated successfully');
            }
        });
    }

    const handleDeleteRide = () => {
        if (selectedRide === undefined) {
            window.alert('Please select a ride to delete!');
            return;
        }
        if (!window.confirm('Are you sure you want to delete this ride?')) {
            return;
        }
        DeleteRide(selectedRide).then(ride => {
            if (ride !== undefined) {
                setRides(rides.filter(r => r.id !== ride.id));
                setSelectedRide(undefined);
                setDestination('');
                setDeparture(null);
                setDestinationError('');
                setDepartureError('');
                window.alert(`Ride with the destination ${ride.destination} and departure` +
                    `${ride.departure.toLocaleString('en-GB', DATE_FORMAT_OPTIONS)} was deleted successfully!`);
            }
        })
    }

    const getRidesTable = () => {
        const columns: Array<Column<Ride>> = [
            {title: 'ID', field: 'id', hidden: true},
            {title: 'Destination', field: 'destination'},
            {title: 'Departure', field: 'departure', type: 'datetime', render: data =>
                    new Date(data.departure).toLocaleString('en-GB', DATE_FORMAT_OPTIONS)},
        ];
        return (
            <MaterialTable
                title='Rides list'
                columns={columns}
                data={rides}
                icons={tableIcons}
                onRowClick={(evt, selectedRow) => {
                    console.log(selectedRow?.departure);
                    if (selectedRide?.id === selectedRow?.id) {
                        setSelectedRide(undefined);
                        setDestination('');
                        setDeparture(null);
                        setDestinationError('');
                        setDepartureError('');
                        return;
                    }
                    if (selectedRow !== undefined) {
                        setSelectedRide(selectedRow);
                        handleDestinationChange(selectedRow.destination);
                        handleDepartureChange(new Date(selectedRow.departure));
                    }
                }}
                options={{
                    rowStyle: rowData => ({
                        backgroundColor: rowData === selectedRide ? '#EEE' : '#FFF'
                    })
                }}
            />
        );
    }

    return (
        <FormControl fullWidth margin='normal' className='centered gap-10'>
            <Typography variant="h2" align='center'>Rides management</Typography>
            <TextField
                label='Destination'
                value={destination}
                onChange={ev => handleDestinationChange(ev.target.value)}
                helperText={destinationError}
                error={destinationError !== ''}
            />
            <DateTimePicker
                label='Departure'
                value={departure}
                format='dd/MM/yyyy HH:mm'
                onChange={handleDepartureChange}
                slotProps={{
                    textField: {
                        helperText: departureError,
                        error: departureError !== ''
                    }
                }}
            />
            <ButtonGroup fullWidth className="gap-5">
                <Button variant='contained' color='success'
                        disabled={destination === '' || !departure || destinationError !== '' || departureError !== ''}
                        onClick={handleAddRide}>
                    Add
                </Button>
                <Button variant='contained' color='warning'
                        disabled={destination === '' || !departure || destinationError !== '' || departureError !== '' || !selectedRide}
                        onClick={handleUpdateRide}>
                    Update
                </Button>
                <Button variant='contained' color='error' disabled={!selectedRide}
                        onClick={handleDeleteRide}>
                    Delete
                </Button>
            </ButtonGroup>
            {getRidesTable()}
        </FormControl>
    );
}