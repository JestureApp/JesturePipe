pub type Result<T> = std::result::Result<T, Box<dyn std::error::Error>>;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum AbslErrorType {
    Cancelled,
    Unknown,
    InvalidArgument,
    DeadlineExceeded,
    NotFound,
    AlreadyExists,
    PermissionDenied,
    ResourceExhausted,
    FailedPrecondition,
    Aborted,
    OutOfRange,
    Unimplemented,
    Internal,
    Unavailable,
    DataLoss,
    Unauthenticated,
}

impl AbslErrorType {
    pub fn from_code(code: i32) -> Self {
        match code {
            1 => AbslErrorType::Cancelled,
            2 => AbslErrorType::Unknown,
            3 => AbslErrorType::InvalidArgument,
            4 => AbslErrorType::DeadlineExceeded,
            5 => AbslErrorType::NotFound,
            6 => AbslErrorType::AlreadyExists,
            7 => AbslErrorType::PermissionDenied,
            8 => AbslErrorType::ResourceExhausted,
            9 => AbslErrorType::FailedPrecondition,
            10 => AbslErrorType::Aborted,
            11 => AbslErrorType::OutOfRange,
            12 => AbslErrorType::Unimplemented,
            13 => AbslErrorType::Internal,
            14 => AbslErrorType::Unavailable,
            15 => AbslErrorType::DataLoss,
            16 => AbslErrorType::Unauthenticated,
            _ => AbslErrorType::Unknown,
        }
    }
}

#[derive(Debug)]
pub struct AbslError {
    pub error_type: AbslErrorType,
    pub message: String,
}

impl std::fmt::Display for AbslError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "AbslError: {:?} - {}", self.error_type, self.message)
    }
}

impl std::error::Error for AbslError {}
